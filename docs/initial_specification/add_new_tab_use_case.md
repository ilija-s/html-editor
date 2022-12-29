**Short description:** The user can add new tabs by opening existing documents or creating new ones, or remove open ones from tab navbar by clicking on the "x" symbol. They can switch between open tabs by using mouse clicks or ctrl+tab shortcut. 

**Actors:**
*User: clicks on certain file on the top of the editor (tab navbar).

**Preconditions:** The application is opened and a new empty document is created.

**Postconditions:** Working directory is changed based on users actions. User can procede to any other user case.

**Main path:**
1. The user opens the application.
2. An empty document is created and opened in the editor - tab that is representing the open document is visible on the top of the editor.
3. The user edits the content of the tab navbar
    3.1 The user creates a new document
        A new empty document is created and it is opened in a new tab in the editor. Go back to step 3.
    3.2 The user opens an existing document
        An existing document is opened and it is added in a new tab in the editor. Go back to step 3.
    3.3 The user closes an opened tab
        3.3.1 The document is not saved
            The editor will ask the user if they want to keep the changes they made to the document, and after saving or discarding the changes it will remove the document from the list of open documents.
        3.3.2 The document is saved
            The document will be removed from the list of open documents.
