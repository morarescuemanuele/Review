#include <library.h>
#include <exceptions.h>

int LibraryItem::generatorId=0;

LibraryItem::LibraryItem(std::string t, std::string a) : id(++generatorId), titlu(t), autor(a), averageRating(0.0f), reviewsCounter(0), sumRating(0){}

std::ostream& operator<<(std::ostream& os, const LibraryItem& item){
    return item.afisare(os);
}

float LibraryItem::getAverageRating() const {
    return averageRating;
}

int LibraryItem::getReviewsCount() const{
    return reviewsCounter;
}

void LibraryItem::averageRatingCalculator(int rating){
    if(rating < 1 || rating > 10){
        throw InvalidInputException("Error: Invalid rating! Must be a value between 1 and 10.");
    }
    sumRating+=rating;
    reviewsCounter++;
    averageRating=(float)sumRating/reviewsCounter;
}

DigitalItem::DigitalItem(std::string t, std::string a, int d) : LibraryItem(t, a), dimensiuneMB(d){}

std::ostream& DigitalItem::afisare(std::ostream& os) const {
    os << "Digital item: " << titlu << " by " << autor << " (" << dimensiuneMB << " MB)";
    return os;
}

std::ostream& EBook::afisare(std::ostream& os) const {
    os << "EBook: " << titlu << " by " << autor;
    return os;
}

EBook::EBook(std::string t, std::string a, int d, std::string f) : DigitalItem(t, a, d), formatFisier(f){}

std::ostream& AudioBook::afisare(std::ostream& os) const {
    os << "AudioBook: " << titlu << " by " << autor;
    return os;
}

AudioBook::AudioBook(std::string t, std::string a, int d, std::string n) : DigitalItem(t, a, d), narator(n){}

std::ostream& PrintedBook::afisare(std::ostream& os) const {
    os << "PrintedBook: " << titlu << " by " << autor;
    return os;
}

PrintedBook::PrintedBook(std::string t, std::string a, int g) : LibraryItem(t, a), greutate(g){}

std::string LibraryItem::getAuthor() const {
    return autor;
}