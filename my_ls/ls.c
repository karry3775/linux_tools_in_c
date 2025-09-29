
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// For converting uid and gid to names
#include <grp.h>
#include <pwd.h>

// For time
#include <stdio.h>
#include <time.h>

void print_permissions(mode_t mode) {
  char perm[11];  // on stack

  // File type
  if (S_ISREG(mode))
    perm[0] = '-';
  else if (S_ISDIR(mode))
    perm[0] = 'd';
  else if (S_ISLNK(mode))
    perm[0] = 'l';
  else
    perm[0] = '?';

  // Owner/User permissions
  perm[1] = (mode & S_IRUSR) ? 'r' : '-';
  perm[2] = (mode & S_IWUSR) ? 'w' : '-';
  perm[3] = (mode & S_IXUSR) ? 'x' : '-';

  // Group
  perm[4] = (mode & S_IRGRP) ? 'r' : '-';
  perm[5] = (mode & S_IWGRP) ? 'w' : '-';
  perm[6] = (mode & S_IXGRP) ? 'x' : '-';

  // Others permissions
  perm[7] = (mode & S_IROTH) ? 'r' : '-';
  perm[8] = (mode & S_IWOTH) ? 'w' : '-';
  perm[9] = (mode & S_IXOTH) ? 'x' : '-';

  perm[10] = '\0';

  printf("%s", perm);
}

void print_user(__uid_t uid) {
  struct passwd* pw = getpwuid(uid);
  if (pw) {
    printf("%s", pw->pw_name);
  } else {
    printf("%d", uid);  // If the pw getting fails
  }
}

void print_group(__gid_t gid) {
  struct group* gr = getgrgid(gid);
  if (gr) {
    printf("%s", gr->gr_name);
  } else {
    printf("%d", gid);  // If the gr fails
  }
}

void print_mtime(time_t t) {
  // Convert to local time
  struct tm* time_info = localtime(&t);
  // Format
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%b %d %H:%M", time_info);
  printf("%s", buffer);
}

// Permissions : -rwxrwxr-x
// Link count  : 1
// User:       : kartik
// Group       : kartik
// Size        : 16088
// Time        : Sep 28 11:43
// kartik kartik 16088 Sep 28 11:43
void print_dir_info(const struct stat* dir_info) {
  print_permissions(dir_info->st_mode);
  printf(" ");
  printf("%ld", dir_info->st_nlink);
  printf(" ");
  print_user(dir_info->st_uid);
  printf(" ");
  print_group(dir_info->st_gid);
  printf(" ");
  printf("%ld", dir_info->st_size);
  printf(" ");
  print_mtime(dir_info->st_mtime);
}

int main(int argc, char** argv) {
  if (argc > 2) {
    printf("Recieved %d args, Can't be > 2", argc);
    printf("Usage:\n");
    printf("$ ./myls // Lists current directory\n");
    printf("$ ./myls /path/to/my_dir // Lists user directory\n");
    return -1;
  }

  char* path = ".";
  if (argc == 2) {
    path = argv[1];
  }

  struct dirent* dent;

  // Load the current directory '.' in dir object
  DIR* dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return -1;
  }

  // Read all the files in the director
  struct stat dir_info;
  while ((dent = readdir(dir)) != NULL) {
    int result = stat(dent->d_name, &dir_info);
    print_dir_info(&dir_info);
    printf(" ");
    printf("%s\n", dent->d_name);
  }

  return 0;
}