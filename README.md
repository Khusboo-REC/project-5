# MP3 Tag Reader

## Project Brief
MP3 tag reader is a software which will read and display MP3 (ID3) tag information from MP3 files. The software will be desktop based and not web based. This solution will read the given MP3 file, extract various tag information and display them via command line. This project can be extended to implement a tag editor, where-in users can modify mp3 tag information.

## Overview
This project focuses on reading and interpreting ID3v2.3 tags from MP3 files. ID3 tags contain metadata about the audio file such as title, artist, album, year, and more.

## Documentation
- `ID3v2.3TagSpec.pdf` - Complete ID3v2.3 tag specification
- `mp3_tag_reader_srs.pdf` - Software Requirements Specification

## Features (Planned/Implemented)
- Read ID3v2.3 tags from MP3 files
- Display metadata information:
  - Title
  - Artist
  - Album
  - Year
  - Genre
  - Comments
- Parse frame headers and data
- Handle different text encodings
- Command-line interface for easy usage

## ID3v2.3 Tag Structure
- Header (10 bytes)
- Extended Header (optional)
- Frames (variable size)
- Padding (optional)
- Footer (optional)

## Technologies Used
- **Advanced C** - Structures, Arrays, File Handling, Pointers, Dynamic Memory Allocation, String Handling
- GCC Compiler
- Metadata Parsing (ID3 tags)

## Key Challenges & Learnings
✓ Parsing and handling MP3 file metadata (ID3 tags) correctly using string operations
✓ Implementing playlist management and playback simulation efficiently using structures and dynamic memory
✓ Understand how to use theory knowledge in practical like file handling, pointers, and dynamic data structures in C
✓ Gained experience in designing modular, menu-driven applications for real-world use cases

## GitHub Repository
https://github.com/Khusboo-REC/project-5

## Future Enhancements
- Support for ID3v2.4 tags
- Tag editing capabilities
- Album art extraction
- Support for other audio formats
