# Use case: Code editing

**Short description:** The user opens the application and a blanc document is opened. The user can edit the blanc document, crate a new document, open an existing document, open a folder, or save the document that is currently opened.

**Actors:** 
- User: Edits HTML documents.

**Preconditions:** The application is opened and a new empty document is created.

**Postconditions:** File is opened, edited, saved or created based on user's choice. The use can continue editing the document or can proceed to any other use case.

**Main path:**
1. The user opens the application.

2. A empty document is created in memory and is opened in the editor.

3. The user edits the content of the open documents.

4. The user can open the menu bar and do one of the following actions:

    4.1. Create a new file. A new empty document is created in memory and opened in a new tab in the editor. Go back to step 3.

    4.2. Open an existing file. A file selection dialog pops up and the selected file is opened inside the editor. Go back to step 3.

    4.3. Open a folder. A folder selection dialog pops up and the selected folder is opened in the file tree view. Go back to step 3.

    4.3. Save to the file system all changes made to a document opened in memory. Go back to step 3.

