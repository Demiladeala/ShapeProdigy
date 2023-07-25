#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <functional>

// Base abstract class for shapes
class Shape
{
protected:
    double height;
    double width;

public:
    // Constructor with default values for height and width
    Shape(double height = 0.0, double width = 0.0) : height(height), width(width) {}
    
    // Pure virtual functions to calculate the perimeter and area of the shape
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
    
    // Pure virtual function to present a quiz question about the shape
    virtual int QuizQuestion() const = 0;
    
    // Virtual destructor to allow proper cleanup when deleting derived class objects
    virtual ~Shape() {}
};

// Derived class for Circle
class Circle final: public Shape
{
private:
    double radius;

public:
    // Constructor for Circle, initializes the radius
    Circle(double radius) : Shape(), radius(radius) {}
    
    // Method to calculate the perimeter of the circle
    double Perimeter() const override { return 2 * M_PI * radius; }
    
    // Method to calculate the area of the circle
    double Area() const override { return M_PI * pow(radius, 2); }
    
    // Method to present a quiz question about the circle
    int QuizQuestion() const override
    {
        std::cout << "A Circle has 0 edges and 0 vertices." << std::endl;
        std::cout << "What is the ";
        int choice = rand() % 2;
        if (choice == 0)
        {
            std::cout << "circumference";
        }
        else
        {
            std::cout << "area";
        }
        std::cout << " of the Circle with radius " << radius << "?\n";
        return choice;
    }
};

// Derived class for Rhombus
class Rhombus final: public Shape
{
private:
    double base;

public:
    // Constructor for Rhombus, initializes the base and height
    Rhombus(double base, double height) : Shape(height), base(base) {}
    
    // Method to calculate the perimeter of the rhombus
    double Perimeter() const override { return 4 * base; }
    
    // Method to calculate the area of the rhombus
    double Area() const override { return base * height; }
    
    // Method to present a quiz question about the rhombus
    int QuizQuestion() const override
    {
        std::cout << "A Rhombus has 4 edges and 4 vertices." << std::endl;
        std::cout << "What is the ";
        int choice = rand() % 2;
        if (choice == 0)
        {
            std::cout << "perimeter";
        }
        else
        {
            std::cout << "area";
        }
        std::cout << " of the Rhombus with base " << base << " and height " << height << "?\n";
        return choice;
    }
};

// Derived class for Rectangle
class Rectangle final: public Shape
{
public:
    // Constructor for Rectangle, initializes the height and width
    Rectangle(double height, double width) : Shape(height, width) {}
    
    // Method to calculate the perimeter of the rectangle
    double Perimeter() const override { return 2 * (height + width); }
    
    // Method to calculate the area of the rectangle
    double Area() const override { return height * width; }
    
    // Method to present a quiz question about the rectangle
    int QuizQuestion() const override
    {
        std::cout << "A Rectangle has 4 edges and 4 vertices." << std::endl;
        std::cout << "What is the ";
        int choice = rand() % 2;
        if (choice == 0)
        {
            std::cout << "perimeter";
        }
        else
        {
            std::cout << "area";
        }
        std::cout << " of the Rectangle with height " << height << " and width " << width << "?\n";
        return choice;
    }
};

// Derived class for Square
class Square final: public Shape
{
private:
    double side;

public:
    // Constructor for Square, initializes the side
    Square(double side) : Shape(), side(side) {}
    
    // Method to calculate the perimeter of the square
    double Perimeter() const override { return 4 * side; }
    
    // Method to calculate the area of the square
    double Area() const override { return side * side; }
    
    // Method to present a quiz question about the square
    int QuizQuestion() const override
    {
        std::cout << "A Square has 4 edges and 4 vertices." << std::endl;
        std::cout << "What is the ";
        int choice = rand() % 2;
        if (choice == 0)
        {
            std::cout << "perimeter";
        }
        else
        {
            std::cout << "area";
        }
        std::cout << " of the Square with side " << side << "?\n";
        return choice;
    }
};

// Derived class for Triangle
class Triangle final: public Shape
{
private:
    double base;

public:
    // Constructor for Triangle, initializes the base and height
    Triangle(double base, double height) : Shape(height), base(base) {}
    
    // Method to calculate the perimeter of the triangle
    double Perimeter() const override { return base + height + std::sqrt(base * base + height * height); }
    
    // Method to calculate the area of the triangle
    double Area() const override { return 0.5 * base * height; }
    
    // Method to present a quiz question about the triangle
    int QuizQuestion() const override
    {
        std::cout << "A Triangle has 3 edges and 3 vertices." << std::endl;
        std::cout << "What is the ";
        int choice = rand() % 2;
        if (choice == 0)
        {
            std::cout << "perimeter";
        }
        else
        {
            std::cout << "area";
        }
        std::cout << " of the Triangle with base " << base << " and height " << height << "?\n";
        return choice;
    }
};

void clearConsole()
{
    std::cout << "Press enter key to continue...";
    std::cin.ignore();
    std::cin.get();
    std::system("cls"); // Use "cls" for Windows
}

double getUserAnswer()
{
    std::string userAnswerString;
    std::cin >> userAnswerString;

    try
    {
        return std::stod(userAnswerString);
    }
    catch(const std::exception& e)
    {
        std::cout << "Try again, use numbers only this time!" << std::endl;
        getUserAnswer();
    }
    
    return 0;
}

// Function to read and retrieve top scores and usernames from "scores.csv" file
std::vector<std::pair<std::string, int>> GetTopScores(const std::string& file_path, int numScores = 10)
{
    std::ifstream scoreFile(file_path);
    if (!scoreFile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return {};
    }

    std::string scoreLine;
    std::vector<std::pair<std::string, int>> scores;

    while (std::getline(scoreFile, scoreLine))
    {
        std::vector<std::string> scoreInfo;
        std::istringstream iss(scoreLine);
        std::string token;

        while (std::getline(iss, token, ','))
        {
            scoreInfo.push_back(token);
        }

        if (scoreInfo.size() == 2)
        {
            std::string username = scoreInfo[0];
            int score = std::stoi(scoreInfo[1]);
            scores.emplace_back(username, score);
        }
    }
    scoreFile.close();

    // Sort the scores in descending order
    std::sort(scores.begin(), scores.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    // Return the top numScores entries
    if (numScores > scores.size())
    {
        numScores = scores.size();
    }
    return std::vector<std::pair<std::string, int>>(scores.begin(), scores.begin() + numScores);
}

int main()
{
    int wait;
    std::ifstream file("shapes.csv");

    if (!file.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    int NuLines = 0;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {

        lines.push_back(line);
        NuLines++;
    }
    file.close();

    int randline;

    // Read and display the top 10 scores and usernames
    std::vector<std::pair<std::string, int>> topScores = GetTopScores("scores.csv");
    int rank = 1;
    std::cout << "---------------------" << std::endl;
    std::cout << "  Top Scores (LEADERBOARD)" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (const auto& scoreEntry : topScores)
    {
        std::cout << rank << ". " << scoreEntry.first << " - " << scoreEntry.second << std::endl;
        rank++;
    }



    // Loop should start here

    // Get the username from the user
    std::string username;
    std::cout << "=================\n";
    std::cout << "Enter your username:\n";
    std::cout << "=================\n";
    std::getline(std::cin, username);

    int score = 0;
    int totalQuestions = 10;

    // Start the quiz
    for (int i = 0; i < totalQuestions; ++i)
    {
        srand(time(NULL));
        randline = rand() % NuLines + 1;
        randline--;
        std::string randText = lines[randline];

        std::vector<std::string> shapeInfo;

        std::istringstream iss(randText);
        std::string token;

        while (std::getline(iss, token, ','))
        {
            shapeInfo.push_back(token);
        }

        std::string shapeName;
        double dimension1, dimension2;

        shapeName = shapeInfo[0];
        dimension1 = std::stod(shapeInfo[1]);
        dimension2 = 0;
        if (shapeInfo.size() > 2)
        {
            dimension2 = std::stod(shapeInfo[2]);
        }
        Shape *shape = nullptr;
        if (shapeName == "Circle")
        {
            shape = new Circle(dimension1);
        }
        else if (shapeName == "Rhombus")
        {
            shape = new Rhombus(dimension1, dimension2);
        }
        else if (shapeName == "Rectangle")
        {
            shape = new Rectangle(dimension1, dimension2);
        }
        else if (shapeName == "Square")
        {
            shape = new Square(dimension1);
        }
        else if (shapeName == "Triangle")
        {
            shape = new Triangle(dimension1, dimension2);
        }
        else
            std::cout << "Can't find shape" << std::endl;
        std::cout << "Question " << (i + 1) << "/" << totalQuestions << std::endl;
        int comChoice = shape->QuizQuestion();

        double userAnswer = getUserAnswer();

        double correctAnswer;
        if (comChoice == 0)
            correctAnswer = shape->Perimeter();
        else
            correctAnswer = shape->Area();

        // Allow a small absolute error in the user's answer
        const double threshold = 0.01;
        double absoluteError = std::abs(userAnswer - correctAnswer);
        if (absoluteError <= threshold)
        {
            score += 10;
            std::cout << "Correct! You scored 10 points.\n Your score is " << score << "/" << (i+1)*10 << std::endl;
        }
        else
        {
            std::cout << "Incorrect! The correct answer is: " << correctAnswer << "\nYour score is " << score << "/" << (i+1)*10 << std::endl;
        }

        clearConsole();
    }

    // Display the final score
    std::cout << "=================\n";
    std::cout << "Quiz Completed!\n";
    std::cout << "=================\n";
    std::cout << "Hello, " << username << "!\n";
    std::cout << "Your final score is: " << score << "/" << (totalQuestions * 10) << std::endl;

    // Store the score in a csv file
    std::ofstream outfile;

    outfile.open("scores.csv", std::ios::app);
    if (outfile.is_open())
    {
        outfile << username << "," << score << std::endl;
        outfile.close();
    }
    else
    {
        std::cout << "Failed to open file for writing" << std::endl;
    }

     // Reading and sorting the scores
    std::ifstream scoreFile("scores.csv");
    if (!scoreFile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    std::string scoreLine;
    std::vector<std::string> scoreVec;
    while (std::getline(scoreFile, scoreLine))
    {
        scoreVec.push_back(scoreLine);
    }
    scoreFile.close();

    std::multimap<int, std::string, std::greater<int>> scoreName;
    for (const auto& element : scoreVec)
    {
        std::vector<std::string> scoreInfo;

        std::istringstream iss(element);
        std::string token;

        while (std::getline(iss, token, ','))
        {
            scoreInfo.push_back(token);
        }
        // scoreInfo[0] === Username ; scoreInfo[1] === score
        scoreName.emplace(std::stoi(scoreInfo[1]), scoreInfo[0]);
    }

    int j = 0;
    std::cout << "---------------------" << std::endl;
    std::cout << "  Top Scores" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (const auto& kvp : scoreName) {
        if (j == 10)
        {
            break;
        } 
        std::cout << kvp.second << " - " << kvp.first << std::endl;
        j++;
    }
    std::cout << "------------------" << std::endl;

    std::cin >> wait;

    return 0;
}