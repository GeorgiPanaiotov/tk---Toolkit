#include "proj.h"

Project loc_init_project()
{
  Project proj;
  proj.file_capacity = FILE_CAPACITY;
  proj.file_count = 0;
  proj.files_skipped = 0;
  proj.total_stats = (Metrics){0, 0, 0, 0};
  proj.files = malloc(proj.file_capacity * sizeof(File));
  return proj;
}

void loc_update_metrics(Project *proj, Metrics *metrics)
{
  proj->total_stats.total += metrics->total;
  proj->total_stats.comment_count += metrics->comment_count;
  proj->total_stats.blank_count += metrics->blank_count;
}

void get_code_total(Project *proj)
{
  proj->total_stats.code_count = proj->total_stats.total - proj->total_stats.blank_count - proj->total_stats.comment_count;
}

void calculate_language_stats(Project *proj)
{
  size_t total_languages = sizeof(language_map) / sizeof(language_map[0]) + 1;
  proj->language_stats = calloc(total_languages, sizeof(LanguageStat));
  proj->language_count = 0;

  for (size_t i = 0; i < proj->file_count; i++)
  {
    char *language = proj->files[i].language;
    int index = -1;

    for (size_t j = 0; j < proj->language_count; j++)
    {
      if (strcmp(proj->language_stats[j].language, language) == 0)
      {
        proj->language_stats[j].count++;
        index = j;
        break;
      }
    }

    if (index == -1)
    {
      index = proj->language_count;
      proj->language_stats[index].language = language;
      proj->language_stats[index].count++;
      proj->language_count++;
    }

    proj->language_stats[index].stats.total += proj->files[i].lines.total;
    proj->language_stats[index].stats.comment_count += proj->files[i].lines.comment_count;
    proj->language_stats[index].stats.blank_count += proj->files[i].lines.blank_count;

    proj->language_stats[index].stats.code_count = proj->language_stats[index].stats.total - proj->language_stats[index].stats.blank_count - proj->language_stats[index].stats.comment_count;
  }
}
