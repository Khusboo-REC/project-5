# MP3 Tag Reader & Editor

## Project Brief
MP3 tag reader is a software which will read and display MP3 (ID3) tag information from MP3 files. The software will be desktop based and not web based. This solution will read the given MP3 file, extract various tag information and display them via command line. This project can be extended to implement a tag editor, where-in users can modify mp3 tag information.

## Overview
A C-based MP3 metadata reader and editor that allows you to read, validate, and update ID3 tags (Title, Artist, Album, Year, Comment) in .mp3 files. The project demonstrates file handling, binary data manipulation, endian conversion, and error checking in C, making it an excellent project for understanding audio file formats and low-level file operations.

## Features

### View Mode
- ✅ Read and display MP3 metadata (ID3 tags)
- ✅ Validate MP3 file format
- ✅ Display all tag information in formatted output
- ✅ Support for ID3v2.3 tag specification

### Edit Mode
- ✅ Modify Title (-t)
- ✅ Modify Artist (-a)
- ✅ Modify Album (-A)
- ✅ Modify Year (-y) with validation (4-digit)
- ✅ Modify Comment (-c)
- ✅ Modify Content/Lyrics (-m)
- ✅ Preserves original audio content after editing
- ✅ Creates backup and safely replaces original file

### Error Handling
- ❌ Invalid year format (must be 4-digit)
- ❌ Wrong file type (non-MP3)
- ❌ Missing command-line arguments
- ❌ Memory allocation failures
- ❌ File read/write errors
- ❌ Invalid tag specifications

## Project Structure
```
MP3_TAG_READER-EDITOR/
├── main.c              # Main program with argument parsing
├── view_mp3.c          # View functionality implementation
├── edit.c              # Edit functionality implementation
├── mp3.h               # Header file with structures and declarations
├── sample.mp3          # Sample MP3 file for testing
├── Daavudi.mp3         # Test file 1
├── Gaali_Vaaluga.mp3   # Test file 2
└── README.md           # Project documentation
```

## Technologies Used
- **Advanced C** - Structures, Arrays, File Handling, Pointers, Dynamic Memory Allocation, String Handling
- **Binary File Operations** - Reading/writing binary data, file positioning
- **Endianness Conversion** - Little-endian to big-endian conversion
- **ID3 Tag Specification** - ID3v2.3 tag format understanding
- **Error Handling** - Robust input validation and error recovery
- **GCC Compiler** - Standard C compilation

## How to Build
```bash
gcc main.c view_mp3.c edit.c -o mp3_editor
```

Or compile individually:
```bash
gcc -c main.c
gcc -c view_mp3.c
gcc -c edit.c
gcc main.o view_mp3.o edit.o -o mp3_editor
```

## How to Use

### View MP3 Tags
```bash
./mp3_editor -v sample.mp3
```

Output:
```
✅ View arguments validated successfully.
✅ File 'sample.mp3' is a valid MP3 file with ID3 tag.

📀 MP3 Tag Information:
  🎵 Title    : Song Name
  👤 Artist   : Artist Name
  💿 Album    : Album Name
  📅 Year     : 2024
  🎼 Content  : Music
  💬 Comment  : Great song
```

### Edit MP3 Tags

#### Change Title
```bash
./mp3_editor -e -t "New Song Title" sample.mp3
```

#### Change Artist
```bash
./mp3_editor -e -a "New Artist Name" sample.mp3
```

#### Change Album
```bash
./mp3_editor -e -A "New Album Name" sample.mp3
```

#### Change Year
```bash
./mp3_editor -e -y 2024 sample.mp3
```

#### Change Comment
```bash
./mp3_editor -e -c "New Comment" sample.mp3
```

#### Multi-word Text (use quotes)
```bash
./mp3_editor -e -t "This Is A Long Title" sample.mp3
```

### Help
```bash
./mp3_editor help
```

## Command-Line Options

| Option | Description | Example |
|--------|-------------|---------|
| `-v` | View MP3 metadata | `./mp3_editor -v file.mp3` |
| `-e` | Edit mode | `./mp3_editor -e -t "Title" file.mp3` |
| `-t` | Change title | `-e -t "New Title"` |
| `-a` | Change artist | `-e -a "New Artist"` |
| `-A` | Change album | `-e -A "New Album"` |
| `-y` | Change year | `-e -y 2024` |
| `-m` | Change content | `-e -m "Music"` |
| `-c` | Change comment | `-e -c "Comment"` |
| `help` | Show help | `./mp3_editor help` |

## How It Works

### View Operation
1. **Validate Arguments** - Check command-line parameters
2. **Open MP3 File** - Open file in binary read mode
3. **Check ID3 Header** - Verify "ID3" magic bytes
4. **Read Tag Data** - Parse ID3v2.3 tag structure
5. **Display Information** - Format and print tag data

### Edit Operation
1. **Validate Arguments** - Check tag option and new value
2. **Open Source File** - Read original MP3 file
3. **Create Temp File** - Create new file for edited version
4. **Copy Header** - Copy ID3 header to new file
5. **Edit Tag** - Replace specified tag with new content
6. **Copy Audio Data** - Preserve original audio content
7. **Replace File** - Remove old file, rename new file

### ID3 Tag Structure
```
ID3 Header (10 bytes):
  - "ID3" (3 bytes)
  - Version (2 bytes)
  - Flags (1 byte)
  - Size (4 bytes, synchsafe integer)

Frame Structure:
  - Frame ID (4 bytes): TIT2, TPE1, TALB, etc.
  - Size (4 bytes)
  - Flags (2 bytes)
  - Data (variable)
```

## Key Challenges & Learnings

✓ **Binary File Handling**: Parsing and handling MP3 file metadata (ID3 tags) correctly using binary file operations and string manipulation

✓ **Endianness Conversion**: Understanding and implementing little-endian to big-endian conversion for proper size calculation

✓ **Data Preservation**: Implementing safe editing that preserves original audio content while modifying only metadata

✓ **Error Handling**: Robust validation for year format, file type, and handling edge cases like memory allocation failures

✓ **Gained practical understanding** of audio file formats, ID3 tag specification, and how to use file handling, pointers, and dynamic data structures in C for real-world applications

## ID3 Frame IDs

| Frame ID | Description |
|----------|-------------|
| TIT2 | Title/Song name |
| TPE1 | Artist/Lead performer |
| TALB | Album name |
| TYER | Year |
| TCON | Content type/Genre |
| COMM | Comments |

## Memory Management
- Dynamic memory allocation for file buffers
- Proper cleanup on errors
- No memory leaks
- Safe string operations

## Validation Rules
- **Year**: Must be exactly 4 digits (e.g., 2024)
- **File Extension**: Must be .mp3
- **ID3 Header**: Must start with "ID3"
- **Arguments**: Correct number and format

## Future Enhancements
- Support for ID3v2.4 tags
- Album art extraction and editing
- Genre selection from predefined list
- Batch processing for multiple files
- GUI interface for easier use
- Support for other audio formats (FLAC, M4A)
- Lyrics editing
- Track number and disc number support

## Sample Output

### View Mode
```
✅ View arguments validated successfully.
✅ File 'sample.mp3' is a valid MP3 file with ID3 tag.

📀 MP3 Tag Information:
  🎵 Title    : Beautiful Song
  👤 Artist   : Famous Artist
  💿 Album    : Greatest Hits
  📅 Year     : 2024
  🎼 Content  : Pop Music
  💬 Comment  : Excellent track
```

### Edit Mode
```
✅ Edit arguments validated successfully.
✅ MP3 Validation Successful: 'sample.mp3' is a valid audio file.

🎉 Successfully updated MP3 file: 'sample.mp3'

📀 Updated MP3 Tag Information:
  🎵 Title    : New Song Title
  👤 Artist   : Famous Artist
  💿 Album    : Greatest Hits
  📅 Year     : 2024
  🎼 Content  : Pop Music
  💬 Comment  : Excellent track
```

## Error Messages
```
❗ Error: Missing command-line arguments.
❌ Error: Invalid arguments for view operation.
❌ Error: The file provided is not a valid MP3 file.
❌ Error: Failed to read MP3 tag data.
💡 Hint: Are you trying to enter more than one word?
📝 If yes, please enter the new text in double quotes
```

## GitHub Repository
https://github.com/Khusboo-REC/project-5

## Learning Outcomes
- Understanding of audio file formats and metadata
- Practical experience with binary file operations
- Knowledge of ID3 tag specification
- Proficiency in file handling and data manipulation
- Error handling and input validation techniques
- Real-world application of C programming concepts

## Credits
Original implementation by G Gangadhar. Enhanced and documented for educational purposes.

---

**Part of Advanced C Programming & File Handling Portfolio**
