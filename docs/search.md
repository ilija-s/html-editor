# Search

**Short description**: The User can click on a *Search* button to search the contents of a file.

**Actors**:
- The User: clicks on a *Search* button.

**Precondition**: Code Editing use case.

**Postcondition**: The Code Editor displays all of the words that match the search.

**Main path**:
1. The User clicks on a *Search* icon.
2. The application opens a search prompt.
3. Until the User presses the `enter` key or `escape` key:
    1. The User types a word they want to search for.
4. If the User pressed the `enter` key:
    1. Application highlights all of the words that match the search.
5. Otherwise if the User pressed the `escape` key:
    1. The search is canceled and the prompt is removed.

**Alternative path**:
- A1: Unexpected application exit: The search is discarded and the applications closes.

**Additional information**: No additional information.
