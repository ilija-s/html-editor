# Use case: Code editing

**Short description:** The user opens the application and blanc document is opened. The user can edit the blanc document, crate a new document, open an existing document or save the document that is currently opened.

**Actors:** 
- User: Edits HTML documents.

**Preconditions:** The application is opened and a new empty document is created.

**Postconditions:** File is opened, edited, saved or created based on user's choice. The use can continue editing the document or can proceed to any other use case.

**Main path:**
1. The user opens the application.

2. A empty document is created in memory and is opened in the editor.

3. The user edits the content of the open documents.

    3.1. The user can open the menu bar and do one of the following actions:

        3.1.1. Create a new file. A new empty document is created in memory and opened in a new tab in the editor. Go back to step 3.

        3.1.2. Open an existing file.

            3.1.2.1. A file selection windows is opened. The user selects a file form the file system.

            3.1.2.2. A document with the contents of the selected file is opened in a new tab in the editor. Go back to step 3.

        3.1.3. Save to the file system all changes made to a document opened in memory. Go back to step 3.

