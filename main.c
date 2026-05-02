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

int main(int argc, char *argv[])
{
    Audio_file audio_File;
    audio_File.fptr_mp3 = NULL;
    audio_File.new_fptr = NULL;

    // for just entered the ./a.out to display the uasage
    if (argc < 2)
    {
        printf("❗ Error: Missing command-line arguments.\n");
        printf("📘 Usage Guide:\n");
        printf("  ▶ View: ./a.out -v <filename.mp3>\n");
        printf("  ▶ Edit: ./a.out -e -t/-a/-A/-m/-y/-c <new_text> <filename.mp3>\n");
        printf("  ▶ Help: ./a.out help\n");
        return 1;
    }

    // if user entered text more than one word then uasage message
    if (argc > 5)
    {
        printf("❌ Error: Incorrect number of arguments for edit operation.\n");
        printf("💡 Hint: Are you trying to enter more than one word?\n");
        printf("📝 If yes, please enter the new text in double quotes like this: \"New Song Title\"\n");
        return 1;
    }

    if (check_operation_type(argv) == help)
    {
        if (argc == 2)
        {
            printf("🔍 Help - Available Options:\n");
            printf("  -v       View MP3 file metadata\n");
            printf("  -e       Edit MP3 file metadata\n");
            printf("    -t     Change song title\n");
            printf("    -a     Change artist name\n");
            printf("    -A     Change album name\n");
            printf("    -y     Change year\n");
            printf("    -m     Change content/lyrics\n");
            printf("    -c     Change comment\n");
            return 0;
        }
        else
        {
            printf("❗ Error: Missing command-line arguments.\n");
            printf("📘 Usage Guide:\n");
            printf("  ▶ View: ./a.out -v <filename.mp3>\n");
            printf("  ▶ Edit: ./a.out -e -t/-a/-A/-m/-y/-c <new_text> <filename.mp3>\n");
            printf("  ▶ Help: ./a.out help\n");
            return 1;
        }
    }

    else if (check_operation_type(argv) == view)
    {
        if (argc == 3)
        {
            // validating the arguments
            if (read_and_validate_view_args(argv, &audio_File) == failure)
            {
                printf("❌ Error: Invalid arguments for view operation.\n");
                return 1;
            }
            printf("✅ View arguments validated successfully.\n");

            // checking the file IDE present or not
            if (check_file(&audio_File) == failure)
            {
                printf("❌ Error: The file provided is not a valid MP3 file.\n");
                return 1;
            }

            printf("✅ File '%s' is a valid MP3 file with ID3 tag.\n\n", audio_File.src_fname);
            if (read_data(&audio_File) == failure)
            {
                printf("❌ Error: Failed to read MP3 tag data.\n");
                return 1;
            }
        }
        else
        {
            printf("❌ Error: Incorrect number of arguments for view operation.\n");
            printf("📘 Correct Usage: ./a.out -v <filename.mp3>\n");
            return 1;
        }
    }
    else if (check_operation_type(argv) == edit)
    {
        if (argc == 5)
        {
            // validating the arguments
            if (read_and_validate_edit_args(argv, &audio_File) == failure)
            {
                printf("❌ Error: Invalid arguments for edit operation.\n");
                return 1;
            }
            printf("✅ Edit arguments validated successfully.\n");

            // checking the file IDE present or not
            if (check_file(&audio_File) == failure)
            {
                printf("❌ Error: The file provided is not a valid MP3 file.\n");
                return 1;
            }

            printf("✅ MP3 Validation Successful: '%s' is a valid audio file.\n\n", audio_File.src_fname);

            if (do_editing(&audio_File) == failure)
            {
                printf("❌ Error: Failed to edit MP3 tag data.\n");
                return 1;
            }
            printf("\n🎉 Successfully updated MP3 file: '%s'\n\n", audio_File.src_fname);

            // for displaying the edited data
            check_file(&audio_File);
            if (read_data(&audio_File) == failure)
            {
                printf("❌ Error: Failed to read the edited MP3 tag data.\n");
                return 1;
            }
        }
        else
        {
            printf("❌ Error: Incorrect number of arguments for edit operation.\n");
            printf("📘 Correct Usage: ./a.out -e -t/-a/-A/-m/-y/-c <new_text> <filename.mp3>\n");
            return 1;
        }
    }
    else
    {
        printf("❗ Error: Missing command-line arguments.\n");
        printf("📘 Usage Guide:\n");
        printf("  ▶ View: ./a.out -v <filename.mp3>\n");
        printf("  ▶ Edit: ./a.out -e -t/-a/-A/-m/-y/-c <new_text> <filename.mp3>\n");
        printf("  ▶ Help: ./a.out help\n");
        return 1;
    }
}
