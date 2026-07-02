#ifndef PROJ_H
#define PROJ_H

#include <stdlib.h>
#include <string.h>

typedef struct Metrics
{
  long long total;
  long comment_count;
  long code_count;
  long blank_count;
} Metrics;

typedef struct File
{
  char *path;
  struct Metrics lines;
  char *language;
} File;

typedef struct LanguageStat
{
  char *language;
  struct Metrics stats;
} LanguageStat;

typedef struct Project
{
  File *files;
  size_t file_count;
  size_t file_capacity;
  size_t files_skipped;
  Metrics total_stats;

  LanguageStat *language_stats;
  size_t language_count;
} Project;

typedef struct LanguageMap
{
  const char *ext;
  char *language;
} LanguageMap;

static const LanguageMap language_map[] = {
    {"c", "C"},
    {"cpp", "C++"},
    {"asm", "Assembly"},
    {"js", "Javascript"},
    {"ts", "Typescript"},
    {"rs", "Rust"},
    {"h", "C/C++ Header"},
    {"cs", "C#"},
    {"cshtml", "C# HTML"},
    {"html", "HTML"},
    {"css", "CSS"},
    {"sh", "Shell Script"},
    {"ml", "OCaml"},
    {"fs", "F#"},
    {"md", "Markdown"},
    {"jsx", "JSX"},
    {"tsx", "TSX"},
    {"py", "Python"},
    {"java", "Java"},
    {"go", "Go"},
    {"ld", "Linker File"},
    {"xml", "XML"},
    {"json", "JSON"},
    {"yml", "YAML"},
    {"sql", "SQL"},
    {"txt", "Text File"},
    {"bat", "Windows Batch File"},
    {"scss", "SCSS"},
    {"php", "PHP"},
    {"svg", "SVG"},
};

#define FILE_CAPACITY 256

Project loc_init_project();
void loc_update_metrics(Project *proj, Metrics *metrics);
void get_code_total(Project *proj);
void calculate_language_stats(Project *proj);

#endif