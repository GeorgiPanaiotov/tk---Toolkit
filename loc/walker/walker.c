#include "walker.h"

static const char *ext_skip[] = {
    "png", "jpeg", "jpg", "dll", "o", "so", "exe", "min.js", "log", "zip", "gz", "tar", "map"};

void loc_walk(Project *proj, char *path, int flags, int modes)
{
  int fd = open(path, flags, modes);
  if (fd == -1)
  {
    perror("walk: open");
    free(proj->files);
    exit(EXIT_FAILURE);
  }

  struct stat st;

  if (fstat(fd, &st) == -1)
  {
    perror("walk: fstat");
    close(fd);
    free(proj->files);
    exit(EXIT_FAILURE);
  }

  if (S_ISDIR(st.st_mode))
  {
    DIR *dir = fdopendir(fd);
    if (!dir)
    {
      perror("walk: fdopendir");
      close(fd);
      free(proj->files);
      exit(EXIT_FAILURE);
    }

    struct dirent *dir_content;

    while ((dir_content = readdir(dir)) != NULL)
    {
      if (loc_skip_dir(dir_content->d_name))
      {
        continue;
      }

      size_t path_len = strlen(path) + strlen(dir_content->d_name) + 2;
      char *fullpath = malloc(path_len);
      if (fullpath == NULL)
      {
        perror("walk: malloc");
        exit(EXIT_FAILURE);
      }
      snprintf(fullpath, path_len, "%s/%s", path, dir_content->d_name);
      loc_walk(proj, fullpath, flags, modes);

      free(fullpath);
    }

    closedir(dir);
  }
  else if (S_ISREG(st.st_mode))
  {
    const char *ext = get_file_ext(path);
    size_t skip_size = sizeof(ext_skip) / sizeof(ext_skip[0]);

    for (size_t i = 0; i < skip_size; i++)
    {
      if (strcmp(ext, ext_skip[i]) == 0)
      {
        proj->files_skipped++;
        close(fd);
        return;
      }
    }

    char *buffer = load_file(&fd);
    close(fd);

    File file = parse_file(buffer, path);

    loc_add_file_to_proj(file, proj);
    free(buffer);
  }
  else
  {
    close(fd);
    return;
  }
}

off_t get_file_size(int *fd)
{
  off_t file_size = lseek(*fd, 0, SEEK_END);
  if (file_size == -1)
  {
    perror("get_file_size: lseek");
    close(*fd);
    exit(EXIT_FAILURE);
  }

  lseek(*fd, 0, SEEK_SET);
  return file_size;
}

char *load_file(int *fd)
{
  ssize_t read_buffer;
  ssize_t read_buffer_total = 0;

  off_t file_size = get_file_size(fd);
  char *buffer = malloc(file_size + 1);
  buffer[file_size] = '\0';

  while (read_buffer_total < file_size)
  {
    read_buffer = read(*fd, buffer + read_buffer_total, file_size - read_buffer_total);
    if (read_buffer == -1)
    {
      perror("read_file: read");
      close(*fd);
      free(buffer);
      exit(EXIT_FAILURE);
    }
    read_buffer_total += read_buffer;
  }

  return buffer;
}

File parse_file(char *buffer, char *path)
{
  File file;
  file.path = strdup(path);

  file.language = get_file_language(path);
  file.lines = (Metrics){0, 0, 0, 0};

  if (buffer[0] == '\0')
  {
    return file;
  }

  size_t i = 0;
  char c;
  while (buffer[i] != '\0')
  {
    c = buffer[i];
    parse_char(&file, c);
    if (check_char(c, '/') && check_char(buffer[i + 1], '/'))
    {
      file.lines.comment_count++;
    }
    if (i > 0)
    {
      if (check_char(c, '\n') && check_char(buffer[i - 1], '\n'))
      {
        file.lines.blank_count++;
      }
    }
    i++;
  }

  if (i > 0 && buffer[i - 1] != '\n')
  {
    file.lines.total++;
  }

  return file;
}

const char *get_file_ext(char *path)
{
  char *dot = strrchr(path, '.');

  if (!dot || dot == path)
  {
    return path;
  }
  return dot + 1;
}

char *get_file_language(char *path)
{
  const char *ext = get_file_ext(path);

  size_t lm_len = sizeof(language_map) / sizeof(language_map[0]);

  for (size_t i = 0; i < lm_len; i++)
  {
    if (strcmp(ext, language_map[i].ext) == 0)
    {
      return language_map[i].language;
    }
  }

  if (strstr(ext, "Make") != NULL || strstr(ext, "make") != NULL)
  {
    return "Make";
  }
  return "Other";
}

void loc_add_file_to_proj(File file, Project *proj)
{
  if (proj->file_count >= proj->file_capacity)
  {
    proj->file_capacity *= 2;

    File *temp_file = realloc(proj->files, proj->file_capacity * sizeof(File));
    if (temp_file == NULL)
    {
      perror("add_file_to_proj: realloc");
      exit(EXIT_FAILURE);
    }
    proj->files = temp_file;
  }
  proj->files[proj->file_count] = file;
  proj->file_count++;
}

bool check_char(char c, char cmp)
{
  return c == cmp;
}

void parse_char(File *file, char c)
{
  if (check_char(c, '\n'))
  {
    file->lines.total++;
    return;
  }
}

bool loc_skip_dir(char *directory)
{
  return strcmp(directory, ".") == 0 || strcmp(directory, "..") == 0 || strcmp(directory, "build") == 0 || strcmp(directory, "node_modules") == 0 || strcmp(directory, "obj") == 0 || strcmp(directory, "bin") == 0;
}
