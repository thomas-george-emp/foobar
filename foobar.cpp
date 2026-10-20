#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Foobar {
private:
  std::string name;
  int position;

public:
  Foobar(std::string &name) : name(name) {}

  virtual int getStrength() { return this->position; }
  std::string &getName() { return this->name; }
  void setPosition(int pos) { this->position = pos; }

protected:
  int getPosition() { return this->position; }
};

class Foo : public Foobar {
public:
  Foo(std::string &name) : Foobar(name) {}
  int getStrength() override { return getPosition() * 3; }
};

class Bar : public Foobar {
public:
  Bar(std::string &name) : Foobar(name) {}
  int getStrength() override { return getPosition() + 15; }
};

void promptUserForFiles(std::string &inputFilePath,
                        std::string &outputFilePath);
std::vector<Foobar *> *createFoobarVector(std::string &inputFile);
void createOutputFoobarFile(std::vector<Foobar *> *foolist,
                            std::string &outputFilePath);
void freeFoobarVector(std::vector<Foobar *> *foolist);

int main(int argc, char *argv[]) {
  std::string inputFile, outputFile;

  promptUserForFiles(inputFile, outputFile);

  std::ofstream ostream(outputFile.c_str());

  std::vector<Foobar *> *foolist = createFoobarVector(inputFile);
  createOutputFoobarFile(foolist, outputFile);

  freeFoobarVector(foolist);
}

void promptUserForFiles(std::string &inputFilePath,
                        std::string &outputFilePath) {
  std::cout << "Enter the name of the input file: ";
  std::cin >> inputFilePath;
  std::cout << "Enter the name of the output file: ";
  std::cin >> outputFilePath;
}

std::vector<Foobar *> *createFoobarVector(std::string &inputFile) {
  std::string word;
  std::stringstream ss;
  std::ifstream istream(inputFile.c_str());
  std::vector<Foobar *> *foolist = new std::vector<Foobar *>;

  int position = 0;

  ss << istream.rdbuf();

  while (std::getline(ss, word, ' ')) {
    Foobar *fooptr = nullptr;
    if (word == "foobar") {
      std::getline(ss, word, '\n');
      fooptr = new Foobar(word);
    }

    else if (word == "bar") {
      std::getline(ss, word, '\n');
      fooptr = new Bar(word);
    }

    else {
      std::getline(ss, word, '\n');
      fooptr = new Foo(word);
    }

    foolist->push_back(fooptr);
  }

  for (size_t i = 0; i < foolist->size(); i++) {
    foolist->at(i)->setPosition((int)(foolist->size() - i));
  }

  return foolist;
}

void createOutputFoobarFile(std::vector<Foobar *> *foolist,
                            std::string &outputFilePath) {
  std::ofstream ostream(outputFilePath);

  for (size_t i = 0; i < foolist->size(); i++) {
    ostream << foolist->at(i)->getName() << ' ' << foolist->at(i)->getStrength()
            << '\n';
  }

  ostream.close();
}

void freeFoobarVector(std::vector<Foobar *> *foolist) {
  for (size_t i = 0; i < foolist->size(); i++) {
    delete foolist->at(i);
  }
  delete foolist;
}
