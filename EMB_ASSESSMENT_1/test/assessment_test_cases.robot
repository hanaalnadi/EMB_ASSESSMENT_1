*** Settings ***
Documentation    Embedded Systems Assessment 1 – Functional Test Cases for UART + DIO

*** Test Cases ***
Test Case 1: LED ON Command ('1')
    [Documentation]    Sending '1' turns LED ON and replies "OK".
    # Arrange
    Ensure LED is OFF to start.
    # Act
    Type 1 in Serial Monitor and press Enter.
    # Assert
    Verify LED turns ON.
    Verify Serial Monitor shows "OK".

Test Case 2: LED OFF Command ('0')
    [Documentation]    Sending '0' turns LED OFF and replies "OK".
    # Arrange
    Ensure LED is ON to start (use Test Case 1 if needed).
    # Act
    Type 0 in Serial Monitor and press Enter.
    # Assert
    Verify LED turns OFF.
    Verify Serial Monitor shows "OK".

Test Case 3: Invalid Command Handling
    [Documentation]    Any non '1'/'0' byte produces "ERR".
    # Arrange
    Pick a character e.g. 'x'.
    # Act
    Type x and press Enter.
    # Assert
    Verify Serial Monitor shows "ERR".
    Verify LED state remains unchanged.

Test Case 4: Button Press/Release Messages (Debounced)
    [Documentation]    Button sends "button_pressed"/"button_released" when pressed and released.
    # Arrange
    Observe Serial Monitor; LED state doesn’t matter.
    # Act
    Press the button firmly then release.
    # Assert
    Verify messages appear in order: "button_pressed" on press, "button_released" on release.
    Verify no duplicate chatter when you do a single clean press (debounce effective).

Test Case 5: Button Press/Release Messages (Debounced) on hold
    [Documentation]    Button sends "button_pressed"/"button_released" once when pressed ad held then released.
    # Arrange
    Observe Serial Monitor; LED state doesn’t matter.
    # Act
    Press and hold the button firmly for a second then release.
    # Assert
    Verify messages appear (once) in order: "button_pressed" on press, "button_released" on release.
    Verify no duplicate chatter when you hold (debounce effective).