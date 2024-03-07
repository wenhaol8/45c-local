#include "compute_grades.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iomanip>


namespace {

    std::string calculate_letter_grade(int score) {
        if (score >= 97) return "A+";
        else if (score >= 93) return "A";
        else if (score >= 90) return "A-";
        else if (score >= 87) return "B+";
        else if (score >= 83) return "B";
        else if (score >= 80) return "B-";
        else if (score >= 77) return "C+";
        else if (score >= 73) return "C";
        else if (score >= 70) return "C-";
        else if (score >= 67) return "D+";
        else if (score >= 63) return "D";
        else if (score >= 60) return "D-";
        else return "F";
    }

    double average(const std::vector<int>& scores, bool drop_lowest) {
        if (scores.empty()) return 0.0;

        int sum = std::accumulate(scores.begin(), scores.end(), 0);
        if (drop_lowest && scores.size() > 1) {
            sum -= *std::min_element(scores.begin(), scores.end());
            return static_cast<double>(sum) / (scores.size() - 1);
        }
        return static_cast<double>(sum) / scores.size();
    }

    void validate_score(int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
    }

}


void Student::validate() const {
    std::for_each(quiz.begin(), quiz.end(), validate_score);
    std::for_each(hw.begin(), hw.end(), validate_score);
    validate_score(static_cast<int>(final_score));
}

void Student::compute_grade() {
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    course_grade = calculate_letter_grade(course_score);
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name <=> other.last_name; cmp != 0) return cmp;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

void Student::compute_quiz_avg() {
    quiz_avg = average(quiz, true);
}

void Student::compute_hw_avg() {
    hw_avg = average(hw, false);
}

void Student::compute_course_score() {
    course_score = std::round(0.4 * quiz_avg + 0.3 * hw_avg + 0.3 * final_score);
}


void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


std::istream& operator>>(std::istream& in, Student& s) {

    s = Student();
    std::string line, keyword;


    if (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> keyword;
        if (keyword == "Name") {
            iss >> s.first_name; // Read the first name
            std::getline(iss, s.last_name); // Read the last name(s)
            rtrim(s.last_name); // Trim trailing whitespace from last name
        }
    }

    if (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> keyword;
        if (keyword == "Quiz") {
            s.quiz = std::vector<int>(std::istream_iterator<int>(iss), {});
        }
    }

    if (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> keyword;
        if (keyword == "HW") {
            s.hw = std::vector<int>(std::istream_iterator<int>(iss), {});
        }
    }

    if (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> keyword;
        if (keyword == "Final") {
            iss >> s.final_score;
        }
    }

    std::getline(in, line);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "Name:   " << s.first_name  << s.last_name << "\n" // Added space between last and first names
        << "HW Ave: " << s.hw_avg << "\n"
        << "QZ Ave: " << s.quiz_avg << "\n"
        << "Final:  " << s.final_score << "\n"
        << "Total:  " << s.course_score << "\n"
        << "Grade:  " << s.course_grade << "\n\n";
    return out;
}

void Gradebook::compute_grades() {
    std::for_each(students.begin(), students.end(), [](Student& s) {
        s.compute_grade();
    });
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate(){
    std::for_each(students.begin(), students.end(), [](const Student& s) {
        s.validate();
    });
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student student;
    while (in >> student) {
        b.students.push_back(student);
        if (in.peek() == '\n') {
            in.ignore();
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const Student& student : b.students) {
        out << student;
    }
    return out;
}