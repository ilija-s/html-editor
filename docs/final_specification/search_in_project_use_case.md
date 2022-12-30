# Find in project

**Short description**: The User can click on a *Find in project* tab and then enter a search query in line edit to search in all of the `.html` and `.css` files in currently opened directory.

**Actors**:
- The User: opens a *Find in project* tab.

**Precondition**: Code Editing use case.

**Postcondition**: The List widget displays all of the lines that match the search alongside the line number and file.

**Main path**:
1. The User opens on a *Find in project* tab and clicks on line edit.
2. The application prompts a user to input the query.
3. Until the User presses the `enter` key or cancels the search:
    1. The User types a query they want to search for.
4. If the User pressed the `enter` key:
    1. The list widget displays a list of strings containing a file name, line number and the whole line that contains the query.
    2. If the User double clicks on an search item:
        1. If the document that is currently opened is saved:
            1. Application opens the file that contains the search query and position the cursor at that line.
        2. Else if the document is not saved the application prompts a User to save the file before opening the file at the given line.

**Alternative path**:
- A1: Unexpected application exit: The search is discarded and the applications closes.

**Additional information**: No additional information.
