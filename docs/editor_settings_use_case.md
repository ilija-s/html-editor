**Short description:** The user can set editor properties like font size, editor theme or view options

**Actor:**
	**User:** clicks on desired property and select offered values.

**Preconditions:** The application is running.

**Postconditions:** Editor properties are changed to selected values.

**Main path:**
1. Application is running (blank document or editing mod)
2. User clicks on EDIT SETTINGS icon from Menu
3. Menu with three choices is opened.
	3.1 Split screen view. Editor window size is changed to fit split screen mod. Go back to step 1.
	3.2. Setting theme
		3.2.1. Window with offered values is opened.
		3.2.2. If one of the themes is selected, editor property is changed. Go back to step 1.
	3.3. Setting font size.
		3.3.1. Window with offered values and input label is opened.
		3.3.2. If one of the themes is selected or entered, editor property is changed. Go back to step 1.