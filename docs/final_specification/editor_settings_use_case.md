**Short** description: The user can set editor properties like font size

**Actor**:
-User: clicks on desired property and select offered values.

**Preconditions**: The application is running.

**Postconditions**: Editor properties are changed to selected values.

**Main path**:
1. Application is running (blank document or editing mod)
2. User clicks on EDITOR SETTINGS icon from Menu
3. Dialog with optional button is opened.

    3.1. Font size is selected and confirmed by clicking on OK button.

        3.1.1  Window with offered values is opened.    
            3.1.1. If entered value is not valid, message is displayed. Go back to previous step.
            3.1.2. If one of the size is selected or entered, editor property is changed. Go to step 3.2.

    3.2. Dialog is accepted.
    3.3. Dialog is rejected by clicking on X button in corner.

4. Dialog is closed and application is running..