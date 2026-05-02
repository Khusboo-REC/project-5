#ifndef MP3_H
#define MP3_H

#define MAX_TAGS 6

#define DATA 100 // Or any appropriate size

typedef struct audio_file
{

    char *src_fname;
    FILE *fptr_mp3;

    char *new_fname;
    char *new_content;
    FILE *new_fptr;

    int tag_index;

} Audio_file;
typedef enum
{
    view,
    edit,
    help,
    unsupported
} OperationType;
typedef enum
{
    success,
    failure
} Status;

//-----------------FOR VIEW------------
OperationType check_operation_type(char *argv[]);

Status read_and_validate_view_args(char *argv[], Audio_file *audio_File);

Status check_file(Audio_file *audio_File);

Status read_tags(Audio_file *audio_File);

Status read_data(Audio_file *audio_File);

Status convert_little_en(char *buffer);

Status compare_tag(char *buffer, int i);

//------------FOR EDIT------------

Status read_and_validate_edit_args(char *argv[], Audio_file *audio_File);

Status check_file_edit(Audio_file *audio_File);

Status copy_header(Audio_file *audio_File);

Status do_editing(Audio_file *audio_File);

Status edit_tag(Audio_file *audio_File);

Status convert_little_end(char *size);

Status copy_remaining_data(FILE *fptr_src, FILE *fptr_dest);

#endif
