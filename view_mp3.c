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

OperationType check_operation_type(char *argv[])
{
    if (strcmp(argv[1], "-v") == 0)
    {
        return view;
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        return edit;
    }
    else if (strcmp(argv[1], "help") == 0)
    {
        return help;
    }
    else
    {
        return unsupported;
    }
}

Status read_and_validate_view_args(char *argv[], Audio_file *audio_File)
{
    char *mp3 = strstr(argv[2], ".mp3");
    if (mp3 == NULL || strcmp(mp3, ".mp3") != 0)
    {
        printf("❌ Error: The input file '%s' does not have a valid .mp3 extension.\n", argv[2]);
        return failure;
    }

    // printf("✅ Input has the Valid .mp3 file extension in '%s'.\n", argv[2]);
    audio_File->src_fname = argv[2];
    return success;
}

Status check_file(Audio_file *audio_File)
{
    printf("🔍 Checking file: %s\n", audio_File->src_fname);
    audio_File->fptr_mp3 = fopen(audio_File->src_fname, "r");

    if (audio_File->fptr_mp3 == NULL)
    {
        perror("fopen");
        fprintf(stderr, "❌ Error: Unable to open source file '%s'.\n", audio_File->src_fname);
        return failure;
    }
    printf("✅ Opened the %s file\n", audio_File->src_fname);
    char buffer[4];
    fread(buffer, 3, 1, audio_File->fptr_mp3);
    buffer[3] = '\0';

    // printf("📄 File signature: '%s'\n", buffer);

    if (strcmp(buffer, "ID3") != 0)
    {
        printf("❌ Error: '%s' is not a valid MP3 file with an ID3 tag.\n", audio_File->src_fname);
        fclose(audio_File->fptr_mp3);
        return failure;
    }

    return success;
}

Status read_data(Audio_file *audio_File)
{
    rewind(audio_File->fptr_mp3);
    fseek(audio_File->fptr_mp3, 10, SEEK_SET);

    printf("\n-------------------------📄 MP3 FILEDATA DETAILS --------------------------\n\n");

    for (int i = 0; i < MAX_TAGS; i++)
    {
        char buffer[5] = {0};

        if (fread(buffer, 4, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Error: Unable to read tag identifier.\n");
            return failure;
        }

        buffer[4] = '\0';

        // comparing the tags where the tags are present or not
        if (compare_tag(buffer, i) == failure)
        {
            printf("❌ Warning: Unknown tag '%s'. Skipping...\n", buffer);

            return failure;
        }

        int size;
        if (fread(&size, 4, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Error: Failed to read tag size.\n");
            return failure;
        }

        convert_little_en((char *)(&size));

        char data_buf[size];
        fseek(audio_File->fptr_mp3, 3, SEEK_CUR);

        if (fread(data_buf, size - 1, 1, audio_File->fptr_mp3) != 1)
        {
            printf("❌ Error: Failed to read tag data.\n");
            return failure;
        }

        data_buf[size - 1] = '\0';

        for (int i = 0; i < size - 1; i++)
        {
            unsigned char ch = data_buf[i];
            if (ch >= 32 && ch <= 126)
                printf("%c", ch);
            else
                printf(".");
        }

        printf("\n");
    }
    printf("\n---------------------------------------------------------------------------\n\n");
    fclose(audio_File->fptr_mp3);
    printf("\n✅ Successfully closed the MP3 file.\n");
    return success;
}

Status convert_little_en(char *num)
{
    char temp;

    temp = num[0];
    num[0] = num[3];
    num[3] = temp;

    temp = num[1];
    num[1] = num[2];
    num[2] = temp;

    return success;
}

Status compare_tag(char *buffer, int i)
{
    const char *arr[] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
    const char *name[] = {"🎵 TITLE", "🎤 ARTIST", "💿 ALBUM", "📅 YEAR", "🎧 GENRE", "💬 COMMENT"};

    if (strcmp(arr[i], buffer) == 0)
    {
        printf("%-20s: ", name[i]);
        return success;
    }

    return failure;
}
