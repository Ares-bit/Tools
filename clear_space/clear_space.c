#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int clear_space(char *file_path)
{
    int ret = 1;
    char line[1000];
    char new_file_name[1000];
    FILE *fp, *fout;
    int i = 0;
    int line_length = 0;
    int file_length = 0;
    int flag = 0;

    fp = fopen(file_path, "r+");
    if (NULL == fp) {
        printf("open file: %s fail.\n", file_path);
        goto exit;
    }

    fseek(fp, 0, SEEK_END);
    file_length = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    strcpy(new_file_name, file_path);
    strcat(new_file_name, "_new.txt");

    fout = fopen(new_file_name, "w");
    if (NULL == fout) {
        printf("create file: %s fail.\n", file_path);
        goto exit;
    }

    while (1)
    {
        fgets(line, 1000, fp);

        line_length = strlen(line);

        if (line_length == 2) {
            i = line_length - 1;
        } else if (line_length > 2) {
            i = line_length - 2;
        }

        flag = 0;

        while (i >= 0 && (line[i] == 0x20 || line[i] == 0x09))
        {
            --i;
            flag = 1;
        }

        if (flag) {
            if (ftell(fp) != file_length) {
                line[++i] = '\n';
            }
            line[++i] = '\0';
        }

        fprintf(fout, "%s", line);

        if (ftell(fp) == file_length) {
            break;
        }
    }

    ret = 0;
    printf("clear %s space success.\n", file_path);

    fclose(fp);
    fclose(fout);

    remove(file_path);
    rename(new_file_name, file_path);

exit:
    return ret;
}

int main(int argc, char *argv[])
{
    int i = 1;
    int ret = 1;

    while (i < argc)
    {
        ret = clear_space(argv[i]);
        if (ret) {
            printf("clear space fail, ret = %d.\n", ret);
            break;
        }
        i++;
    }

    return ret;
}