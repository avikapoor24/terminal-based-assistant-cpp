# 🖥️ Terminal-Based Personal Assistant

A lightweight, C++ terminal-based personal assistant that helps manage **tasks, attendance, academic performance, and schedules** efficiently.

---

## 📜 Features

✅ **Task Manager** - Add, remove, and mark tasks as completed.  
✅ **Attendance Tracker** - Mark attendance, view history, and calculate attendance percentage.  
✅ **Timetable Manager** - Organize schedules and avoid conflicts.  
✅ **Marks Tracker** - Keep track of subject-wise academic performance.  
✅ **Secure Authentication** - SHA-256-based password hashing for security.

---

## 🚀 Installation & Setup

### **1️⃣ Clone the Repository**

```bash
https://github.com/avikapoor24/terminal-based-assistant-cpp.git
cd chatbotassistant
```

### **2️⃣ Install Dependencies**

```bash
brew install openssl
```

### **3️⃣ Compile the Project**

```bash
make
```

### **4️⃣ Run the Assistant**

```bash
./assistant
```

## 🛠️ Project Structure
```bash
/YOUR_REPO_NAME
│── main.cpp                # Main driver file
│── /include                # Header files
│   │── TaskManager.h       # Task management
│   │── Attendance.h        # Attendance tracking
│   │── MarksTracker.h      # Academic performance tracking
│   │── Timetable.h         # Schedule tracking
│   │── Admin.h             # User authentication
│── /src                    # Implementation files
│   │── TaskManager.cpp     
│   │── Attendance.cpp     
│   │── MarksTracker.cpp   
│   │── Timetable.cpp      
│   │── Admin.cpp          
│── /data                   # Persistent storage
│   │── tasks.txt
│   │── attendance.txt
│   │── marks.txt
│   │── timetable.txt
│── .gitignore              # Ignored files
│── Makefile                # Build automation
│── README.md               # Documentation
```

## 📝 Usage
### **📌 Task Management:**

```bash
1. Add a task  
2. View all tasks  
3. Mark task as complete  
4. Delete task 
```

### **📊 Attendance Tracking:**

```bash
1. Mark attendance  
2. View attendance history  
3. Calculate attendance percentage  
```

### **📅 Timetable & Academic Tracking:**

```bash
1. Add a subject  
2. Remove a subject  
3. View schedule  
```

### **🔐 Admin Features:**

```bash
1. Login  
2. Change username/password  
3. View account details  
```

## 🏗️ Future Enhancements
🚀 Data export/import functionality
🚀 Multi-language support
🚀 Cloud backup integration
🚀 Graphical analytics for performance tracking

## 🤝 Contributing
### 💡 Found a bug? Want to add a new feature?
Fork the repository
- Create a new branch (feature-branch)
- Commit changes (git commit -m "Added new feature")
- Push changes (git push origin feature-branch)
- Create a Pull Request

## 🚀 Ready to organize your work? Run ./assistant now!
