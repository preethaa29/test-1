#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class Task {
public:
    std::string name;
    std::string dueDate;
    int priority;

    Task(const std::string& taskName, const std::string& taskDueDate, int taskPriority)
        : name(taskName), dueDate(taskDueDate), priority(taskPriority) {}
};

class ToDoListApp {
private:
    std::vector<Task> tasks;

public:
    void displayMenu() {
        std::cout << "\nToDo List App\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Tasks\n";
        std::cout << "3. Update Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
    }

    void addTask() {
        std::string taskName, taskDueDate;
        int taskPriority;

        std::cout << "Enter the task name: ";
        std::getline(std::cin, taskName);

        std::cout << "Enter the due date (optional): ";
        std::getline(std::cin, taskDueDate);

        std::cout << "Enter the priority (1 - Low, 2 - Medium, 3 - High): ";
        std::cin >> taskPriority;
        std::cin.ignore(); // Consume the newline character

        tasks.emplace_back(taskName, taskDueDate, taskPriority);
        std::cout << "Task added successfully!\n";
    }

    void viewTasks() {
        std::cout << "\nTasks:\n";
        if (tasks.empty()) {
            std::cout << "No tasks available.\n";
        } else {
            std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
                return a.priority > b.priority; // Sort by priority (descending order)
            });

            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << (i + 1) << ". " << tasks[i].name;
                if (!tasks[i].dueDate.empty()) {
                    std::cout << " (Due: " << tasks[i].dueDate << ")";
                }
                std::cout << " - Priority: " << tasks[i].priority << '\n';
            }
        }
    }

    void updateTask() {
        viewTasks();
        std::cout << "Enter the task number to update: ";
        size_t taskNumber;
        std::cin >> taskNumber;
        std::cin.ignore(); // Consume the newline character

        if (isValidTaskNumber(taskNumber)) {
            std::string updatedTaskName, updatedDueDate;
            int updatedPriority;

            std::cout << "Enter the updated task name: ";
            std::getline(std::cin, updatedTaskName);

            std::cout << "Enter the updated due date (optional): ";
            std::getline(std::cin, updatedDueDate);

            std::cout << "Enter the updated priority (1 - Low, 2 - Medium, 3 - High): ";
            std::cin >> updatedPriority;
            std::cin.ignore(); // Consume the newline character

            tasks[taskNumber - 1].name = updatedTaskName;
            tasks[taskNumber - 1].dueDate = updatedDueDate;
            tasks[taskNumber - 1].priority = updatedPriority;
            std::cout << "Task updated successfully!\n";
        } else {
            std::cout << "Invalid task number. Please try again.\n";
        }
    }

    void deleteTask() {
        viewTasks();
        std::cout << "Enter the task number to delete: ";
        size_t taskNumber;
        std::cin >> taskNumber;
        std::cin.ignore(); // Consume the newline character

        if (isValidTaskNumber(taskNumber)) {
            tasks.erase(tasks.begin() + taskNumber - 1);
            std::cout << "Task deleted successfully!\n";
        } else {
            std::cout << "Invalid task number. Please try again.\n";
        }
    }

    bool isValidTaskNumber(size_t taskNumber) {
        return taskNumber >= 1 && taskNumber <= tasks.size();
    }

    void saveTasksToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& task : tasks) {
                outFile << task.name << "," << task.dueDate << "," << task.priority << "\n";
            }
            std::cout << "Tasks saved to file.\n";
        } else {
            std::cout << "Unable to open the file for saving tasks.\n";
        }
    }

    void loadTasksFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            tasks.clear(); // Clear existing tasks
            std::string line;
            while (std::getline(inFile, line)) {
                std::size_t pos1 = line.find(',');
                std::size_t pos2 = line.find(',', pos1 + 1);
                std::string taskName = line.substr(0, pos1);
                std::string dueDate = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int priority = std::stoi(line.substr(pos2 + 1));
                tasks.emplace_back(taskName, dueDate, priority);
            }
            std::cout << "Tasks loaded from file.\n";
        } else {
            std::cout << "Unable to open the file for loading tasks.\n";
        }
    }
};

int main() {
    ToDoListApp app;
    std::string filename = "tasks.txt"; // Change the filename as needed

    app.loadTasksFromFile(filename);

    while (true) {
        app.displayMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Consume the newline character

        switch (choice) {
            case 1:
                app.addTask();
                break;
            case 2:
                app.viewTasks();
                break;
            case 3:
                app.updateTask();
                break;
            case 4:
                app.deleteTask();
                break;
            case 5:
                app.saveTasksToFile(filename);
                std::cout << "Exiting the application. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
