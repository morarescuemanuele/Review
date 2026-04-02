#pragma once
#include <string>
#include <iostream>

// Am 2 tipuri de iteme:
//      Digital:
//          EBook
//          Audiobook
//      Fizic:
//          PrintedBook

class LibraryItem{
protected:
    std::string titlu, autor;
    static int generatorId;
    int id;
    float averageRating;
    int reviewsCounter, sumRating;

public:
    LibraryItem(std::string t, std::string a);
    virtual ~LibraryItem() = default;

    void averageRatingCalculator(int rating);

    float getAverageRating() const;
    int getReviewsCount() const;

    virtual std::ostream& afisare(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const LibraryItem&);
    std::string getAuthor() const;
};


class DigitalItem : public LibraryItem{
protected:
    int dimensiuneMB;
public:
    DigitalItem(std::string t, std::string a, int d);

    std::ostream& afisare(std::ostream& os) const override;

};

class EBook : public DigitalItem{
    std::string formatFisier;
public:
    EBook(std::string t, std::string a, int d, std::string f);
    std::ostream& afisare(std::ostream& os) const override;

};

class AudioBook : public DigitalItem{
    std::string narator;
public:
    AudioBook(std::string t, std::string a, int d, std::string n);
    std::ostream& afisare(std::ostream& os) const override;
};

class PrintedBook : public LibraryItem{
    int greutate;
public:
    PrintedBook(std::string t, std::string a, int g);
    std::ostream& afisare(std::ostream& os) const override;
};