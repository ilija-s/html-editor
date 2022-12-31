# Parse HTML document

**Short description**: When the User saves the document that is currently being edit the application parses the html file and displays the warning and error messages if the document is not valid.

**Actors**:
- The User: saves the document.

**Precondition**: Code Editing use case.

**Postcondition**: The List widget displays all of messages that the parser produced.

**Main path**:
1. The User saves a document that is being edited.
2. The application runs the validator and returns the list of messages if there are any.
3. The messages are displayed inside if the list widget.

**Alternative path**:
- A1: Unexpected application exit: The search is discarded and the applications closes.

**Additional information**: No additional information.
