# HW1 Spell Checker — Cover Page & Summary

## Cover Page

**Assignment number:** HW1 (Spell Checker)  
**Student name(s):** ________________________________  
**Student ULID:** _________________________________  
**Secret directory:** ______________________________  
**Course:** IT279 Data Structures  
**Date:** _________________________________  

---

## Brief Summary (Approach)

This program reads a dictionary word list, converts all words to lowercase, and inserts each unique word into a `Dictionary` data structure. It then reads the input text file and extracts words, treating any non-letter character as a delimiter. For each word that is not found in the dictionary, the program reports the misspelling along with the line number.

For suggested corrections, the program generates candidate words using these single-step rules and checks each candidate against the dictionary:

- Add one letter (a–z) at any position
- Remove one letter
- Exchange adjacent characters

## Difficulties / How I Resolved Them (optional extra credit)

- **Input parsing:** Converting to lowercase and splitting on non-letters consistently across dictionary and text files.
- **Duplicates:** Avoiding duplicate inserts into the dictionary by checking membership before inserting.
- **Output formatting:** Matching the required spelling-output format exactly (line numbers, indentation, blank lines).

