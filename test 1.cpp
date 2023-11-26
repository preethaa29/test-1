#include <iostream>
#include <vector>

class ToDoListApp {
private:
    std::vector<std::string> tasks;

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
        std::string task;
        std::cout << "Enter the task: ";
        std::getline(std::cin, task);
        tasks.push_back(task);
        std::cout << "Task added successfully!\n";
    }

    void viewTasks() {
        std::cout << "\nTasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << (i + 1) << ". " << tasks[i] << '\n';
        }
    }

    void updateTask() {
        viewTasks();
        std::cout << "Enter the task number to update: ";
        size_t taskNumber;
        std::cin >> taskNumber;
        std::cin.ignore(); // Consume the newline character

        if (isValidTaskNumber(taskNumber)) {
            std::string updatedTask;
            std::cout << "Enter the updated task: ";
            std::getline(std::cin, updatedTask);
            tasks[taskNumber - 1] = updatedTask;
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
};

int main() {
    ToDoListApp app;

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
                std::cout << "Exiting the application. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
