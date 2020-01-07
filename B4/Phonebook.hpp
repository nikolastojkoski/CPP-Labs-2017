#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <set>

struct PhonebookEntry
{
  std::string number;
  std::string name;
};
class Phonebook
{
public:

  Phonebook();
  Phonebook(const Phonebook &other);
  Phonebook(Phonebook &&other) = default;
  
  Phonebook& operator=(const Phonebook &other);
  Phonebook& operator=(Phonebook &&other) = default;

  void addEntry(const PhonebookEntry &entry);
  void addBookmark(const std::string &currentBookmark, const std::string &newBookmark);
  void insertBefore(const std::string &boomark, const PhonebookEntry &entry);
  void insertAfter(const std::string &bookmark, const PhonebookEntry &entry);
  void deleteEntry(const std::string &bookmark);
  void replaceEntry(const std::string &bookmark, const PhonebookEntry &entry);
  void showEntryName(const std::string &bookmark, std::ostream &out);
  void moveBoomark(const std::string &bookmark, int steps);
  void moveBoomark(const std::string &bookmark, const std::string &location);
  void moveToNext(const std::string &bookmark);
  void moveToPrev(const std::string &bookmark);

private:

  struct EntryElem
  {
    PhonebookEntry entry;
    std::set<std::string> bookmarks;
  };

  typedef std::list<EntryElem> entries_type;
  typedef std::map<std::string, entries_type::iterator> bookmarks_type;
  typedef bookmarks_type::iterator bookmarksIt_type;

  entries_type entries_;
  bookmarks_type bookmarks_;

  bookmarksIt_type getIterator(const std::string & bookmark);
};


#endif
