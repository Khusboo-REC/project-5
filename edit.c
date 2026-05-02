/*
Documentation
Name        :G Gangadhar
Date        :08/08/2025
Description :Mp3 Reader and Editor
*/
#include <stdio.h>
#include "mp3.h"
#include <string.h>
#include <stdlib.h>

Status read_and_validate_edit_args(char *argv[], Audio_file *audio_File)
{
    if (argv[2] == NULL)
    {
        printf("❌ Error: Missing tag option (-t / -a / -A / -y / -m / -c)\n");
        return failure;
    }

    const char *arr[] = {"-t", "-a", "-A", "-y", "-m", "-c"};
    int flag = 0;

    // comparing with tags input tag
    for (int i = 0; i < MAX_TAGS; i++)
    {
        if (strcmp(arr[i], argv[2]) == 0)
        {
            flag = 1;
            audio_File->tag_index = i;
        }
    }
    // validation for year
    if (strcmp(argv[2], "-y") == 0)
    {
        char *tag = argv[3];
        int len = strlen(tag);
        if (len != 4)
        {
            printf("❌ Invalid year: Please enter a valid 4-digit year (e.g., 1999, 2024).\n");
            return failure;
        }
        int i = 0;

        while (tag[i])
        {
            if (tag[i] < '0' || tag[i] > '9')
            {
                printf("❌ Invalid year: Please enter a valid 4-digit year (e.g., 1999, 2024).\n");
                return failure;
            }
            i++;
        }
    }
    if (!flag)
    {
        printf("❌ Error: Invalid tag option '%s'. Use -t/-a/-A/-y/-m/-c\n", argv[2]);
        return failure;
    }

    if (argv[3] == NULL)
    {
        printf("❌ Error: Missing new content to edit.\n");
        return failure;
    }

    audio_File->new_content = argv[3];

    char *ch = strstr(argv[4], ".mp3");
    if (ch == NULL || strcmp(ch, ".mp3") != 0)
    {
        printf("❌ Error: Invalid filename '%s'. Must be an .mp3 file.\n", argv[4]);
        return failure;
    }

    audio_File->src_fname = argv[4];
    // assigning the new file name
    audio_File->new_fname = "new_file.mp3";

    return success;
}

Status do_editing(Audio_file *audio_File)
{
    // coping the header function
    if (copy_header(audio_File) == failure)
    {
        printf("❌ Error copying MP3 header.\n");
        return failure;
    }
    printf("✅ Header copied successfully.\n");

    // here tag edit takes place
    if (edit_tag(audio_File) == failure)
    {
        printf("❌ Error editing tag data.\n");
        return failure;
    }
    printf("✅ Tag data edited successfully.\n\n");

    // coping the remaning data as it is
    if (copy_remaining_data(audio_File->fptr_mp3, audio_File->new_fptr) == failure)
    {
        printf("❌ Error copying remaining MP3 data.\n");
        return failure;
    }
    // printf("✅ Remaining MP3 data copied successfully.\n");

    // removing old file . and adding old name to new file
    if (remove(audio_File->src_fname) == 0 && rename(audio_File->new_fname, audio_File->src_fname) == 0)
    {

        return success;
    }
    else
    {
        printf("❌ Error replacing original file with the edited file data.\n");
        return failure;
    }
}

Status copy_header(Audio_file *audio_File)
{
    rewind(audio_File->fptr_mp3);
    // assigning the new file name
    audio_File->new_fname = "new.mp3";
    // opening the new file
    audio_File->new_fptr = fopen(audio_File->new_fname, "w");
    if (audio_File->new_fptr == NULL)
    {
        perror("fopen");
        printf("❌ Error opening new file '%s' for writing.\n", audio_File->new_fname);
        return failure;
    }

    char *buffer[10];
    if (fread(buffer, 10, 1, audio_File->fptr_mp3) != 1)
    {
        printf("❌ Failed to read header from source file.\n");
        return failure;
    }
    fwrite(buffer, 10, 1, audio_File->new_fptr);
    return success;
}

Status edit_tag(Audio_file *audio_File)
{
    for (int i = 0; i <= audio_File->tag_index; i++)
    {
        char buffer[4];

        if (fread(buffer, 4, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Failed to read tag identifier.\n");
            return failure;
        }
        fwrite(buffer, 4, 1, audio_File->new_fptr);

        int size, new_size = 0;
        int s_flag = 0;

        if (fread(&size, 4, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Failed to read tag size.\n");
            return failure;
        }
        convert_little_end((char *)&size);

        if (i == audio_File->tag_index)
        {
            new_size = strlen(audio_File->new_content) + 1;
            int temp = new_size;
            convert_little_end((char *)&temp);
            fwrite(&temp, 4, 1, audio_File->new_fptr);
            s_flag = 1;
        }

        if (!s_flag)
        {
            int temp = size;
            convert_little_end((char *)&temp);
            fwrite(&temp, 4, 1, audio_File->new_fptr);
        }

        char flag[3];
        if (fread(flag, 3, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Failed to read tag flags.\n");
            return failure;
        }
        fwrite(flag, 3, 1, audio_File->new_fptr);

        char *data_buf = malloc(size);
        if (!data_buf)
        {
            fprintf(stderr, "❌ Memory allocation failed while reading tag data.\n");
            return failure;
        }

        if (fread(data_buf, size - 1, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Failed to read tag content.\n");
            free(data_buf);
            return failure;
        }

        if (i == audio_File->tag_index)
        {
            fwrite(audio_File->new_content, new_size - 1, 1, audio_File->new_fptr);
        }
        else
        {
            fwrite(data_buf, size - 1, 1, audio_File->new_fptr);
        }

        free(data_buf);
    }
    return success;
}

Status convert_little_end(char *size)
{
    unsigned char temp;

    // Swap byte 0 with byte 3
    temp = size[0];
    size[0] = size[3];
    size[3] = temp;

    // Swap byte 1 with byte 2
    temp = size[1];
    size[1] = size[2];
    size[2] = temp;

    return success;
}

Status copy_remaining_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;
    printf("Coping the remaining data...\n");
    while (fread(&ch, 1, 1, fptr_src) == 1)
    {
        if (fwrite(&ch, 1, 1, fptr_dest) != 1)
        {
            printf("❌ Error writing remaining byte to destination.\n");
            return failure;
        }
    }
    // closing the file's
    fclose(fptr_dest);
    fclose(fptr_src);
    printf("✅ Remaining MP3 data copied successfully.\n");
    printf("✅ Successfully closed the editing files\n");
    return success;
}
