#include "collector.h"

void mu_walk(ProjectStats *proj, char *path, int flags, int modes)
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
      if (mu_skip_dir(dir_content->d_name))
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

      mu_walk(proj, fullpath, flags, modes);

      free(fullpath);
    }

    proj->total_stats.total_dir_size += st.st_size;
    proj->total_stats.total_dir_footprint_size += st.st_blocks * BLOCK_SIZE;
    closedir(dir);
  }
  else if (S_ISREG(st.st_mode))
  {
    File file;
    file.path = strdup(path);
    file.size = st.st_size;
    file.footprint_size = st.st_blocks * BLOCK_SIZE;

    mu_update_metrics(proj, file.size, file.footprint_size);

    close(fd);
    mu_add_file_to_proj(file, proj);
  }
  else
  {
    close(fd);
    return;
  }
}

void mu_add_file_to_proj(File file, ProjectStats *proj)
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

bool mu_skip_dir(char *directory)
{
  return strcmp(directory, ".") == 0 || strcmp(directory, "..") == 0;
}
