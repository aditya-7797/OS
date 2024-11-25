#!/bin/sh

print_list() {
  reset
  echo "(1) - Search Employee"
  echo "(2) - Add an Employee entry"
  echo "(3) - Remove an Employee entry"
  echo "(4) - For quit the app, press 4, goodbye..."
  echo "Select the number of your choice on the list, or quit by pressing q"
}

read_record() {
  RECORD=$1
  MATCHES=$(grep -w "$RECORD" employee.txt)
  
  if [ -z "$MATCHES" ]; then
    echo "No records found for: $RECORD"
    return
  fi

  echo "Matching record(s):"
  echo "$MATCHES"
}

insert_record() {
  echo "Please enter Employee ID:"
  read ID
  echo "Please enter Employee name:"
  read NAME
  echo "Please enter Employee phone number:"
  read PHONE 
  echo "Please enter Employee email ID:"
  read EMAIL
  echo "Adding employee address book entry..."
  echo "$ID $NAME $PHONE $EMAIL" >> employee.txt
  echo "Data inserted!"
}

remove_record() {
  DATA=$1
  echo "Searching for records matching: $DATA"
  MATCHES=$(grep -w "$DATA" employee.txt)
  
  if [ -z "$MATCHES" ]; then
    echo "No records found matching: $DATA"
    return
  fi

  echo "Matching record(s):"
  echo "$MATCHES"
  echo "Do you want to delete these records? (y/n)"
  read CONFIRM

  if [ "$CONFIRM" = "y" ]; then
    echo "Removing Employee entry..."
    sed -i "/$DATA/d" employee.txt
    echo "Record(s) deleted successfully!"
  else
    echo "Deletion canceled."
  fi
}

go_back() {
  echo "To return to the main menu, press 'm'. To quit, press 'q'."
  read CHOICE_MENU
  if [ "$CHOICE_MENU" = "m" ]; then
    print_list
  elif [ "$CHOICE_MENU" = "q" ]; then
    exit 0
  else 
    echo "Invalid choice. Please enter 'm' to continue or 'q' to quit."
  fi
}

echo "Welcome to Employee Address Book"

print_list
read CHOICE

while [ "$CHOICE" -ne 4 ]
do
  case $CHOICE in
    1)
      echo "Please enter employee ID, name, phone number, or email to search:"
      read QUERY
      read_record "$QUERY"
      go_back
      ;;
    2)
      insert_record
      go_back
      ;;
    3)
      echo "Please enter employee ID, name, phone number, or email to remove:"
      read USER
      remove_record "$USER"
      go_back
      ;;
    *)
      echo "Invalid choice. Please select a valid option."
      ;;
  esac
  print_list
  read CHOICE
done

echo "Goodbye!"
