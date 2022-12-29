# Use case: File Tree View manipulation

**Short description:** The user can manipulate working directory using file tree view. The user can open an existing document and move through project directories. Manipulation is done with mouse clicks.

**Actors:** 
- User: opens project folder and file tree view shows.

**Preconditions:** The application is running and file tree view is opened.

**Postconditions:** Selected html file is opened in editor. User can procede to any other user case.

**Main path:**
1. The user opens the application.
2. User opens project directory through 'Open folder' option in menu bar.
2. File tree view is opened and user can see it.
3. The user is moving through working directory until he decides to do something else.
    3.1. The user can click on any folder and all contents of that folder will show.
    3.2. The user can double click on certain file and it should be opened in editor. Go back to step 3.
4. Application is running , html file is opened (if chosen), and user can procede to do whatever he wants.