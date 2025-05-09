#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <stdexcept>
#include <algorithm>

class UniversitySystemException : public std::runtime_error {
public:
    UniversitySystemException(const std::string &message)
        : std::runtime_error(message) {}
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(const std::string &message)
        : UniversitySystemException(message) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(const std::string &message)
        : UniversitySystemException(message) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(const std::string &message)
        : UniversitySystemException(message) {}
};

class Course;
class Department;
class Professor;

class Person {
protected:
    std::string name;
    int age;
    std::string id;
    std::string contactInfo;

public:
    Person(const std::string& name, int age, const std::string& id, const std::string& contactInfo) {
        setName(name);
        setAge(age);
        setId(id);
        setContactInfo(contactInfo);
    }
    
    virtual ~Person() {}

    std::string getName() const { return name; }
    void setName(const std::string& n) {
        if (n.empty())
            throw UniversitySystemException("Name cannot be empty.");
        name = n;
    }
    
    int getAge() const { return age; }
    void setAge(int a) {
        if (a <= 0 || a > 120)
            throw UniversitySystemException("Age must be positive and reasonable.");
        age = a;
    }
    
    std::string getId() const { return id; }
    void setId(const std::string& identifier) {
        if (identifier.empty())
            throw UniversitySystemException("ID cannot be empty.");
        id = identifier;
    }
    
    std::string getContactInfo() const { return contactInfo; }
    void setContactInfo(const std::string& ci) {
        if (ci.empty())
            throw UniversitySystemException("Contact information cannot be empty.");
        contactInfo = ci;
    }
    
    // Virtual method for polymorphic display
    virtual void displayDetails() const {
        std::cout << "ID: " << id << ", Name: " << name 
                  << ", Age: " << age << ", Contact: " << contactInfo << std::endl;
    }
    
    // Virtual method for payment. Default is 0.0.
    virtual double calculatePayment() const { return 0.0; }
};


// Student class: Inherits from Person and adds attributes such as enrollment date, program and GPA.
class Student : public Person {
protected:
    std::string enrollmentDate;  // For simplicity using string representation of date
    std::string program;
    double GPA;
    // Aggregation: a student can enroll in several courses.
    std::vector<Course*> enrolledCourses;
    
public:
    Student(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
            const std::string& enrollmentDate, const std::string& program, double GPA)
      : Person(name, age, id, contactInfo), enrollmentDate(enrollmentDate), program(program)
    {
        setGPA(GPA);
    }
    
    void setGPA(double g) {
        if (g < 0.0 || g > 4.0)
            throw UniversitySystemException("GPA must be between 0.0 and 4.0.");
        GPA = g;
    }
    
    double getGPA() const { return GPA; }
    
    std::string getEnrollmentDate() const { return enrollmentDate; }
    void setEnrollmentDate(const std::string& dt) { enrollmentDate = dt; }
    
    std::string getProgram() const { return program; }
    void setProgram(const std::string& prog) { program = prog; }
    
    void enrollCourse(Course* course) {
        enrolledCourses.push_back(course);
    }
    
    const std::vector<Course*>& getEnrolledCourses() const {
        return enrolledCourses;
    }
    
    // Override displayDetails to include student-specific information.
    void displayDetails() const override {
        Person::displayDetails();
        std::cout << "Enrollment Date: " << enrollmentDate 
                  << "\nProgram: " << program << "\nGPA: " << GPA << std::endl;
    }
    
    // For students, payment calculation is not implemented.
    double calculatePayment() const override {
        return 0.0;
    }
};


// Professor class: Inherits from Person and adds attributes like department, specialization, and hire date.
class Professor : public Person {
protected:
    std::string department;
    std::string specialization;
    std::string hireDate;
    
public:
    Professor(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
              const std::string& department, const std::string& specialization, const std::string& hireDate)
      : Person(name, age, id, contactInfo), department(department), specialization(specialization), hireDate(hireDate)
    {
    }
    
    std::string getDepartment() const { return department; }
    void setDepartment(const std::string& dept) {
       if(dept.empty())
           throw UniversitySystemException("Department cannot be empty.");
       department = dept;
    }
    
    std::string getSpecialization() const { return specialization; }
    void setSpecialization(const std::string& spec) {
       if(spec.empty())
           throw UniversitySystemException("Specialization cannot be empty.");
       specialization = spec;
    }
    
    std::string getHireDate() const { return hireDate; }
    void setHireDate(const std::string& dt) { hireDate = dt; }
    
    void displayDetails() const override {
        Person::displayDetails();
        std::cout << "Department: " << department 
                  << ", Specialization: " << specialization 
                  << ", Hire Date: " << hireDate << std::endl;
    }
    
    double calculatePayment() const override {
        return 5000.0;
    }
};

class Course {
private:
    std::string code;
    std::string title;
    int credits;
    std::string description;
    Professor* instructor; 
    
public:
    Course(const std::string& code, const std::string& title, int credits, const std::string& description)
      : code(code), title(title), credits(credits), description(description), instructor(nullptr)
    {
        if (code.empty() || title.empty())
            throw UniversitySystemException("Course code and title cannot be empty.");
        if (credits <= 0)
            throw UniversitySystemException("Course credits must be positive.");
    }
    
    std::string getCode() const { return code; }
    std::string getTitle() const { return title; }
    int getCredits() const { return credits; }
    std::string getDescription() const { return description; }
    
    void setInstructor(Professor* prof) { instructor = prof; }
    Professor* getInstructor() const { return instructor; }
    
    void displayDetails() const {
        std::cout << "Course Code: " << code << ", Title: " << title 
                  << ", Credits: " << credits << std::endl;
        std::cout << "Description: " << description << std::endl;
        if(instructor)
            std::cout << "Instructor: " << instructor->getName() << std::endl;
    }
};

class Department {
private:
    std::string name;
    std::string location;
    double budget;
    std::vector<Professor*> professors;
    
public:
    Department(const std::string& name, const std::string& location, double budget)
      : name(name), location(location), budget(budget)
    {
        if(name.empty())
            throw UniversitySystemException("Department name cannot be empty.");
        if(budget < 0)
            throw UniversitySystemException("Budget must not be negative.");
    }
    
    std::string getName() const { return name; }
    std::string getLocation() const { return location; }
    double getBudget() const { return budget; }
    
    void addProfessor(Professor* prof) {
        professors.push_back(prof);
    }
    
    const std::vector<Professor*>& getProfessors() const {
        return professors;
    }
    
    void displayDetails() const {
        std::cout << "Department: " << name << ", Location: " << location 
                  << ", Budget: " << budget << std::endl;
    }
};


class GradeBook {
private:
    std::map<std::string, double> grades; 
public:
    void addGrade(const std::string& studentId, double grade) {
        if(grade < 0.0 || grade > 100.0)
            throw GradeException("Grade must be between 0 and 100.");
        grades[studentId] = grade;
    }
    
    double calculateAverageGrade() const {
        if(grades.empty())
            return 0.0;
        double total = 0.0;
        for(auto const &pair: grades)
            total += pair.second;
        return total / grades.size();
    }
    
    double getHighestGrade() const {
        if(grades.empty())
            return 0.0;
        double highest = 0.0;
        for(auto const &pair: grades)
            if(pair.second > highest)
                highest = pair.second;
        return highest;
    }
    
    std::vector<std::string> getFailingStudents(double passingGrade = 60.0) const {
        std::vector<std::string> failing;
        for(auto const &pair: grades)
            if(pair.second < passingGrade)
                failing.push_back(pair.first);
        return failing;
    }
};


class EnrollmentManager {
private:
    std::map<std::string, std::vector<std::string>> enrollmentData;
    std::map<std::string, int> courseCapacities;
    
public:
    void setCourseCapacity(const std::string& courseCode, int capacity) {
        if(capacity <= 0)
            throw EnrollmentException("Course capacity must be positive.");
        courseCapacities[courseCode] = capacity;
    }
    
    void enrollStudent(const std::string& courseCode, const std::string& studentId) {
        int capacity = courseCapacities.count(courseCode) ? courseCapacities[courseCode] : 30; 
        auto &enrolled = enrollmentData[courseCode];
        if(static_cast<int>(enrolled.size()) >= capacity)
            throw EnrollmentException("Cannot enroll student: course is full.");
        enrolled.push_back(studentId);
    }
    
    void dropStudent(const std::string& courseCode, const std::string& studentId) {
        auto &enrolled = enrollmentData[courseCode];
        auto it = std::find(enrolled.begin(), enrolled.end(), studentId);
        if(it != enrolled.end())
            enrolled.erase(it);
        else
            throw EnrollmentException("Student not found in course.");
    }
    
    int getEnrollmentCount(const std::string& courseCode) const {
        if(enrollmentData.find(courseCode) != enrollmentData.end())
            return enrollmentData.at(courseCode).size();
        return 0;
    }
};


class UndergraduateStudent : public Student {
private:
    std::string major;
    std::string minor;
    std::string expectedGraduationDate;
    
public:
    UndergraduateStudent(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
                           const std::string& enrollmentDate, const std::string& program, double GPA,
                           const std::string& major, const std::string& minor, const std::string& expectedGraduationDate)
      : Student(name, age, id, contactInfo, enrollmentDate, program, GPA),
        major(major), minor(minor), expectedGraduationDate(expectedGraduationDate)
    {
    }
    
    void displayDetails() const override {
        Student::displayDetails();
        std::cout << "Undergraduate - Major: " << major 
                  << ", Minor: " << minor 
                  << ", Expected Graduation: " << expectedGraduationDate << std::endl;
    }
};

class GraduateStudent : public Student {
private:
    std::string researchTopic;
    Professor* advisor; // Aggregation: an advisor is a professor
    std::string thesisTitle;
    
public:
    GraduateStudent(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
                    const std::string& enrollmentDate, const std::string& program, double GPA,
                    const std::string& researchTopic, Professor* advisor, const std::string& thesisTitle)
      : Student(name, age, id, contactInfo, enrollmentDate, program, GPA),
        researchTopic(researchTopic), advisor(advisor), thesisTitle(thesisTitle)
    {
    }
    
    void displayDetails() const override {
        Student::displayDetails();
        std::cout << "Graduate - Research Topic: " << researchTopic 
                  << ", Thesis Title: " << thesisTitle << std::endl;
        if(advisor)
            std::cout << "Advisor: " << advisor->getName() << std::endl;
    }
};

class AssistantProfessor : public Professor {
private:
    int yearsOfService;
    double baseSalary;
    
public:
    AssistantProfessor(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
                       const std::string& department, const std::string& specialization, const std::string& hireDate,
                       int yearsOfService, double baseSalary)
      : Professor(name, age, id, contactInfo, department, specialization, hireDate),
        yearsOfService(yearsOfService), baseSalary(baseSalary)
    {
    }
    
    void displayDetails() const override {
        Professor::displayDetails();
        std::cout << "Assistant Professor - Years of Service: " << yearsOfService 
                  << ", Base Salary: " << baseSalary << std::endl;
    }
    
    double calculatePayment() const override {
        return baseSalary + (yearsOfService * 100); 
    }
};

class AssociateProfessor : public Professor {
private:
    int yearsOfService;
    double baseSalary;
    double bonus;
    
public:
    AssociateProfessor(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
                       const std::string& department, const std::string& specialization, const std::string& hireDate,
                       int yearsOfService, double baseSalary, double bonus)
      : Professor(name, age, id, contactInfo, department, specialization, hireDate),
        yearsOfService(yearsOfService), baseSalary(baseSalary), bonus(bonus)
    {
    }
    
    void displayDetails() const override {
        Professor::displayDetails();
        std::cout << "Associate Professor - Years of Service: " << yearsOfService 
                  << ", Base Salary: " << baseSalary << ", Bonus: " << bonus << std::endl;
    }
    
    double calculatePayment() const override {
        return baseSalary + (yearsOfService * 150) + bonus;
    }
};

class FullProfessor : public Professor {
private:
    int yearsOfService;
    double baseSalary;
    double bonus;
    double researchGrant;
    
public:
    FullProfessor(const std::string& name, int age, const std::string& id, const std::string& contactInfo,
                  const std::string& department, const std::string& specialization, const std::string& hireDate,
                  int yearsOfService, double baseSalary, double bonus, double researchGrant)
      : Professor(name, age, id, contactInfo, department, specialization, hireDate),
        yearsOfService(yearsOfService), baseSalary(baseSalary), bonus(bonus), researchGrant(researchGrant)
    {
    }
    
    void displayDetails() const override {
        Professor::displayDetails();
        std::cout << "Full Professor - Years of Service: " << yearsOfService 
                  << ", Base Salary: " << baseSalary 
                  << ", Bonus: " << bonus 
                  << ", Research Grant: " << researchGrant << std::endl;
    }
    
    double calculatePayment() const override {
        return baseSalary + (yearsOfService * 200) + bonus + researchGrant;
    }
};

class University {
private:
    std::vector<Department*> departments;
public:
    void addDepartment(Department* dept) {
        departments.push_back(dept);
    }
    
    void removeDepartment(const std::string& deptName) {
        auto it = std::remove_if(departments.begin(), departments.end(),
                                 [&](Department* d){ return d->getName() == deptName; });
        if(it != departments.end())
            departments.erase(it, departments.end());
    }
    
    std::vector<Professor*> getAllProfessors() const {
        std::vector<Professor*> profs;
        for(auto dept : departments) {
            const auto& deptProfs = dept->getProfessors();
            profs.insert(profs.end(), deptProfs.begin(), deptProfs.end());
        }
        return profs;
    }
    
    void displayUniversityDetails() const {
        for(auto dept : departments) {
            dept->displayDetails();
            for(auto prof : dept->getProfessors()) {
                prof->displayDetails();
            }
        }
    }
};


class Classroom {
private:
    std::string roomNumber;
    int capacity;
public:
    Classroom(const std::string& roomNumber, int capacity)
      : roomNumber(roomNumber), capacity(capacity)
    {
        if(roomNumber.empty() || capacity <= 0)
            throw UniversitySystemException("Invalid parameters.");
    }
      
    std::string getRoomNumber() const { return roomNumber; }
    int getCapacity() const { return capacity; }
};

class Schedule {
private:
    std::map<std::string, std::pair<std::string, Classroom*>> courseSchedule;
public:
    void addSchedule(const std::string& courseCode, const std::string& timeSlot, Classroom* room) {
        courseSchedule[courseCode] = std::make_pair(timeSlot, room);
    }
    
    void displaySchedule() const {
        for(auto const& entry: courseSchedule) {
            std::cout << "Course: " << entry.first << ", Time: " << entry.second.first
                      << ", Room: " << entry.second.second->getRoomNumber() << std::endl;
        }
    }
};


class UniversitySystem {
private:
    University university;
    EnrollmentManager enrollmentManager;
    GradeBook gradeBook;
    std::vector<Course*> courses;
    std::vector<Student*> students;
    std::vector<Professor*> professors;
    
public:
    UniversitySystem() {}
    
    void addDepartment(Department* dept) {
        university.addDepartment(dept);
    }
    
    void addCourse(Course* c) { courses.push_back(c); }
    void addStudent(Student* s) { students.push_back(s); }
    void addProfessor(Professor* p) { 
        professors.push_back(p);
    }
    
    EnrollmentManager& getEnrollmentManager() { return enrollmentManager; }
    GradeBook& getGradeBook() { return gradeBook; }
    
    void generateReports() {
        std::cout << "\n--- University Report ---\n";
        std::cout << "Students:\n";
        for(auto s : students)
            s->displayDetails();
        std::cout << "\nCourses:\n";
        for(auto c : courses)
            c->displayDetails();
    }
    
    void runDemo() {
        try {
            std::cout << "\nCreating new semester...\n";
            if(!courses.empty() && students.size() >= 2) {
                enrollmentManager.setCourseCapacity(courses[0]->getCode(), 2);
                enrollmentManager.enrollStudent(courses[0]->getCode(), students[0]->getId());
                enrollmentManager.enrollStudent(courses[0]->getCode(), students[1]->getId());
                try {
                    enrollmentManager.enrollStudent(courses[0]->getCode(), "ExtraStudent");
                } catch(const EnrollmentException& e) {
                    std::cout << "Enrollment Exception: " << e.what() << std::endl;
                }
            }
            
            // Process grades:
            gradeBook.addGrade(students[0]->getId(), 85.0);
            gradeBook.addGrade(students[1]->getId(), 55.0);  // failing grade
            std::cout << "\nAverage Grade: " << gradeBook.calculateAverageGrade() << std::endl;
            std::cout << "Highest Grade: " << gradeBook.getHighestGrade() << std::endl;
            auto failing = gradeBook.getFailingStudents();
            std::cout << "Failing Students: ";
            for(auto id : failing)
                std::cout << id << " ";
            std::cout << std::endl;
            
            std::cout << "\nPayment Calculations:\n";
            for(auto p : professors) {
                std::cout << p->getName() << " Payment: " << p->calculatePayment() << std::endl;
            }
            
        } catch(const UniversitySystemException& ex) {
            std::cerr << "System Exception: " << ex.what() << std::endl;
        }
    }
};


int main() {
    try {
        UniversitySystem uniSystem;
        
        Department* csDept = new Department("Computer Science", "A", 1234567);
        uniSystem.addDepartment(csDept);
        
        Professor* prof1 = new AssistantProfessor("Dr. Mohan", 42, "9891", "mohan.kumar@gmail.com",
                                                   "Computer Science", "ML", "2014-07-18",
                                                   190, 9000.0);
        csDept->addProfessor(prof1);
        uniSystem.addProfessor(prof1);
        
        Course* course1 = new Course("CSE001", "Programming Intro", 7, "Basics ");
        course1->setInstructor(prof1);
        uniSystem.addCourse(course1);
        
        Student* student1 = new UndergraduateStudent("Arbab", 19, "ABC1", "ansari@gmail.com", 
                                                       "2023-09-01", "BTech CSE", 3.9,
                                                       "CSE", "Math", "2028-05-30");
                                                       
        Student* student2 = new GraduateStudent("Aditya", 25, "SDF1", "aditya@yahoo.com", 
                                                  "2022-09-01", "MTech CSE", 3.8,
                                                  "ML Research", prof1, "Machine Learning Approaches");
        uniSystem.addStudent(student1);
        uniSystem.addStudent(student2);
        
        student1->enrollCourse(course1);
        student2->enrollCourse(course1);
        
        uniSystem.runDemo();
        
        uniSystem.generateReports();
        
        delete csDept;
        delete course1;
        delete student1;
        delete student2;
        delete prof1;
        
    } catch(const UniversitySystemException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}