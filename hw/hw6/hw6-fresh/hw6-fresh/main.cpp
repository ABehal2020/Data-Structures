//
//  main.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "constraint.hpp"
#include "wordinput.hpp"
#include "puzzle.hpp"
#include "wordsolution.hpp"
#include "wordcombination.hpp"

using namespace std;

// reading words from dictionary file into vector
// O(d)
void parseDictionary(ifstream& dictionary, vector<WordInput>& dictionaryWords) {
    string word;
    while (dictionary >> word) {
        dictionaryWords.push_back(WordInput(word, word.size()));
    }
}

// parsing puzzle file
// O((h + c + z)(c + w) + (c*log(c)))
void parsePuzzleInput(ifstream& puzzleInput, vector<Constraint>& constraints,
                      vector<vector<char> >& board) {
    string puzzleLine;
    vector<char> puzzleLineVector;
    // O(h + c + z)
    while (puzzleInput >> puzzleLine) {
        // ignore lines starting with !
        if (puzzleLine[0] == '!') {
            continue;
        } else if (puzzleLine[0] == '+') {
            // keep track of length and frequency of constraints
            bool found = false;
            unsigned int constraintLength = stoi(puzzleLine.substr(1));
            // O(c)
            for (unsigned int i = 0; i < constraints.size(); i++) {
                if (constraints[i].getLength() == constraintLength) {
                    constraints[i].incrementFrequency();
                    found = true;
                }
            }
            if (!found) {
                constraints.push_back(Constraint(constraintLength, 1));
            }
        } else {
            // add this line to crossword puzzle board
            // O(w)
            for (string::iterator itr = puzzleLine.begin(); itr !=
                 puzzleLine.end(); itr++) {
                // O(1)
                puzzleLineVector.push_back(*itr);
            }
            board.push_back(puzzleLineVector);
            puzzleLineVector.clear();
        }
    }
    // O(c*log(c))
    sort(constraints.begin(), constraints.end(), constraintLength);
}

// O(w)
bool searchAcross(const Puzzle& grid, const WordInput& word,
    unsigned int wordLength, unsigned int rowSearchIndex, unsigned int
    colSearchIndex, unsigned int currentLetterIndex) {
    // if word search progresses to size of word, we have found the word
    if (wordLength == 0) {
        return true;
    }
    /* check to see if letter matches corresponding word letter
      if it does, recurse */
    if (grid.getBoard()[rowSearchIndex][colSearchIndex] ==
        word.getWord()[currentLetterIndex]) {
        return searchAcross(grid, word, wordLength - 1, rowSearchIndex,
                            colSearchIndex + 1, currentLetterIndex + 1);
    } else {
        return false;
    }
}

// O(h)
bool searchDown(const Puzzle& grid, const WordInput& word, unsigned int
                wordLength, unsigned int rowSearchIndex, unsigned int
                colSearchIndex, unsigned int currentLetterIndex) {
    // if word search progresses to size of word, we have found the word
    if (wordLength == 0) {
        return true;
    }
    /* check to see if letter matches corresponding word letter
    if it does, recurse */
    if (grid.getBoard()[rowSearchIndex][colSearchIndex] ==
        word.getWord()[currentLetterIndex]) {
        return searchDown(grid, word, wordLength - 1, rowSearchIndex + 1,
                          colSearchIndex, currentLetterIndex + 1);
    } else {
        return false;
    }
}

// searching for words in puzzle
// O(d*h*w*(w + h) + f*log(f))
void searchWords(const Puzzle& grid, const vector<WordInput>& dictionaryWords,
                 vector<WordSolution>& wordsFound) {
    bool foundWord = false;
    // O(d)
    for (unsigned int i = 0; i < dictionaryWords.size(); i++) {
        // O(h)
        for (unsigned int j = 0; j < grid.getRows(); j++) {
            // O(w)
            for (unsigned int k = 0; k < grid.getCols(); k++) {
                // O(1)
                if (grid.getBoard()[j][k] == dictionaryWords[i].getWord()[0]) {
                    // ensuring search is possible (within boundaries of grid)
                    // O(1)
                    if (grid.searchAcrossPossible(dictionaryWords[i], j, k)) {
                        // O(w)
                        if (searchAcross(grid, dictionaryWords[i],
                                         dictionaryWords[i].getLength() - 1, j,
                                         k + 1, 1)) {
                            foundWord = true;
                            // keep track of found words
                            wordsFound.push_back(WordSolution(dictionaryWords[i]
                                                , "across", Point(j, k)));
                            break;
                        }
                    }
                    // ensuring search is possible (within boundaries of grid)
                    // O(1)
                    if (grid.searchDownPossible(dictionaryWords[i], j, k)) {
                        // O(h)
                        if (searchDown(grid, dictionaryWords[i],
                                       dictionaryWords[i].getLength() - 1, j + 1
                                       , k, 1)) {
                            foundWord = true;
                            // keep track of found words
                            wordsFound.push_back(WordSolution(dictionaryWords[i]
                                                        , "down", Point(j, k)));
                            break;
                        }
                    }
                }
            }
            if (foundWord) {
                foundWord = false;
                break;
            }
        }
    }
    // O(f*log(f))
    sort(wordsFound.begin(), wordsFound.end(), wordLength);
}

// find all possible combinations in a vector given the length of a combination
// O(fCc) (this denotes O(f choose c) for combinations (f!/((f-c)!*c!)
void Combinations(vector<WordSolution> a, int requiredLength, int start,
    int currentLength, vector<bool>& checking, vector<WordSolution>& wordCombos)
{
    if (currentLength > requiredLength) {
        return;
    } else if (currentLength == requiredLength) {
        for (unsigned int i = 0; i < a.size(); i++) {
            if (checking[i] == true) {
                // keep track of unique combinations
                wordCombos.push_back(a[i]);
            }
        }
        return;
    }
    if (start == (int)a.size()) {
        return;
    }
    // recurse to progress further down the vector to new elements
    checking[start] = true;
    Combinations(a, requiredLength, start + 1, currentLength + 1, checking,
                 wordCombos);
    checking[start] = false;
    Combinations(a, requiredLength, start + 1, currentLength, checking,
                 wordCombos);
}

// find combinations among word combinations
// O(fCc)
void MetaCombinations(vector<WordCombination> a, int requiredLength, int start,
    int currentLength, vector<bool>& checking, vector<WordCombination>&
                      metaWordCombos)
{
    if (currentLength > requiredLength) {
        return;
    } else if (currentLength == requiredLength) {
        for (unsigned int i = 0; i < a.size(); i++) {
            if (checking[i] == true) {
                // keep track of unique combinations
                metaWordCombos.push_back(a[i]);
            }
        }
        return;
    }
    if (start == (int)a.size()) {
        return;
    }
    // recurse to progress further down the vector to new elements
    checking[start] = true;
    MetaCombinations(a, requiredLength, start + 1, currentLength + 1, checking,
                     metaWordCombos);
    checking[start] = false;
    MetaCombinations(a, requiredLength, start + 1, currentLength, checking,
                     metaWordCombos);
}

// make combinations from words
// O(c*fCc) simplified from O(f*c + c*(fCc)) as c*(fCc) > f*c
void generateCombinations(const vector<Constraint>& constraints,
                          const vector<WordSolution>& wordsFound,
                          vector<vector<WordSolution>>& combinationsResult) {
    vector<WordSolution> wordsFoundRefined;
    // O(f)
    for (unsigned int i = 0; i < wordsFound.size(); i++) {
        // O(c)
        for (unsigned int j = 0; j < constraints.size(); j++) {
            if ((int)wordsFound[i].getLength() ==
                (int)constraints[j].getLength()) {
                wordsFoundRefined.push_back(wordsFound[i]);
                break;
            }
        }
    }
    
    // preparing combinations list to pass onto recursive combinations function
    vector<vector<WordSolution> > combinationsInput;
    vector<WordSolution> wordsSameLength;
    // O(c)
    for (unsigned int i = 0; i < constraints.size(); i++) {
        // O(f)
        for (unsigned int j = 0; j < wordsFoundRefined.size(); j++) {
            if ((int)constraints[i].getLength() ==
                (int)wordsFoundRefined[j].getLength()) {
                wordsSameLength.push_back(wordsFoundRefined[j]);
            }
        }
        combinationsInput.push_back(wordsSameLength);
        wordsSameLength.clear();
    }
    
    // keep track of unique combinations among words
    vector<WordSolution> wordCombos;
    int counter = 0;
    // O(c)
    for (unsigned int i = 0; i < combinationsInput.size(); i++) {
        vector<bool> check = {false};
        // O(fCc)
        Combinations(combinationsInput[i], constraints[counter].getFrequency(),
                     0, 0, check, wordCombos);
        counter++;
        combinationsResult.push_back(wordCombos);
        wordCombos.clear();
    }
}

// flatten combinations
// O(c*fCc*x)
void flattenCombinations(vector<vector<WordSolution>>& combinationsResult,
    const vector<Constraint>& constraints, vector<WordSolution>& words,
    vector<vector<WordSolution>>& singleCombo,
    vector<vector<vector<WordSolution>>>& allPossibleCombos,
                         vector<WordCombination>& flattenedCombos) {
    int counter = 0;
    unsigned int cycles = 0;
    // merge combinations into categories of their individual word lengths
    // O(c)
    for (unsigned int i = 0; i < combinationsResult.size(); i++) {
        // O(f)
        for (unsigned int j = 0; j < combinationsResult[i].size(); j++) {
            if (cycles < constraints[counter].getFrequency()) {
                words.push_back(combinationsResult[i][j]);
                cycles++;
            } else {
                singleCombo.push_back(words);
                words.clear();
                words.push_back(combinationsResult[i][j]);
                cycles = 1;
            }
        }
        singleCombo.push_back(words);
        allPossibleCombos.push_back(singleCombo);
        words.clear();
        singleCombo.clear();
        cycles = 0;
        counter++;
    }
    
    // complete merge process into individual categories
    WordCombination flattenedWord;
    // O(c)
    for (unsigned int i = 0; i < allPossibleCombos.size(); i++) {
        // O(fCc)
        for (unsigned int j = 0; j < allPossibleCombos[i].size(); j++) {
            // O(x)
            for (unsigned int k = 0; k < allPossibleCombos[i][j].size(); k++) {
                flattenedWord += allPossibleCombos[i][j][k];
            }
            flattenedCombos.push_back(flattenedWord);
            flattenedWord.clear();
        }
    }
}

// throw out extraneous meta combinations
// O(((fCc)^2)/(c^2)*log(fCc)
void filterMetaCombinations(vector<WordCombination>& metaWordCombos,
    vector<vector<vector<WordSolution>>>& allPossibleCombos,
    vector<WordCombination>& singleMetaCombo,
    vector<vector<WordCombination>>& allMetaWordCombos,
    vector<vector<WordCombination>>& filteredAllMetaWordCombos) {
    int counter = 0;
    // O(fCc)
    for (unsigned int i = 0; i < metaWordCombos.size(); i++) {
        if (counter != (int)allPossibleCombos.size()) {
            singleMetaCombo.push_back(metaWordCombos[i]);
            counter++;
        } else if (counter == (int)allPossibleCombos.size()) {
            allMetaWordCombos.push_back(singleMetaCombo);
            singleMetaCombo.clear();
            singleMetaCombo.push_back(metaWordCombos[i]);
            counter++;
            counter = 1;
        }
    }
    
    // sort meta combinations by indvidual word length
    // O(fCc/c)
    for (unsigned int i = 0; i < allMetaWordCombos.size(); i++) {
        // O(fCc/c*log(fCc))
        sort(allMetaWordCombos[i].begin(), allMetaWordCombos[i].end(),
             individualWordLength);
    }
    
    allMetaWordCombos.push_back(singleMetaCombo);
    singleMetaCombo.clear();
    vector<WordCombination> singleFilteredMetaCombo;
    // if meta combinations contain unique elements, keep them
    // O(fCc/c)
    for (unsigned int i = 0; i < allMetaWordCombos.size(); i++) {
        // O(c)
        for (unsigned int j = 0; j < allMetaWordCombos[i].size() - 1; j++) {
            if (allMetaWordCombos[i][j].getIndividualLength() !=
                allMetaWordCombos[i][j + 1].getIndividualLength()) {
                singleFilteredMetaCombo.push_back(allMetaWordCombos[i][j]);
            } else {
                singleFilteredMetaCombo.clear();
                break;
            }
        }
        singleFilteredMetaCombo.push_back(
                        allMetaWordCombos[i][allMetaWordCombos[i].size() - 1]);
        if (!singleFilteredMetaCombo.empty()) {
            filteredAllMetaWordCombos.push_back(singleFilteredMetaCombo);
            singleFilteredMetaCombo.clear();
        }
    }
}

// find unique word combinations
// O(c*fCc*x + (fCc)^2/(c^2)*log(fCc)
void findWordCombinations(const vector<Constraint>& constraints,
    const vector<WordSolution>& wordsFound, vector<vector<WordSolution> >&
                          allWordCombinations) {
    vector<vector<WordSolution> > combinationsResult;
    // generate unique combinations of elements
    // O(c*fCc)
    generateCombinations(constraints, wordsFound, combinationsResult);
    vector<vector<vector<WordSolution>>> allPossibleCombos;
    vector<vector<WordSolution>> singleCombo;
    vector<WordSolution> words;
    vector<WordCombination> flattenedCombos;
    // flatten the result of combinations
    // O(c*fCc*x)
    flattenCombinations(combinationsResult, constraints, words, singleCombo,
                        allPossibleCombos, flattenedCombos);
    vector<WordCombination> metaWordCombos;
    vector<WordCombination> singleMetaCombo;
    vector<vector<WordCombination>> allMetaWordCombos;
    vector<bool> metaCheck = {false};
    // find meta combinations
    // O(fCc)
    MetaCombinations(flattenedCombos, allPossibleCombos.size(), 0, 0, metaCheck,
                     metaWordCombos);
    vector<vector<WordCombination>> filteredAllMetaWordCombos;
    // O(((fCc)^2)/(c^2)*log(fCc)
    filterMetaCombinations(metaWordCombos, allPossibleCombos, singleMetaCombo,
                           allMetaWordCombos, filteredAllMetaWordCombos);
    vector<WordSolution> wordSolutionSingleCombo;
    vector<WordSolution> returnSplitMultipleWords;
    // split up word combinations into individual words
    // O(fCc/c)
    for (unsigned int i = 0; i < filteredAllMetaWordCombos.size(); i++) {
        // O(c)
        for (unsigned int j = 0; j < filteredAllMetaWordCombos[i].size(); j++) {
            returnSplitMultipleWords =
            filteredAllMetaWordCombos[i][j].splitMultipleWords();
            wordSolutionSingleCombo.insert(wordSolutionSingleCombo.end(),
            returnSplitMultipleWords.begin(), returnSplitMultipleWords.end());
        }
        allWordCombinations.push_back(wordSolutionSingleCombo);
        wordSolutionSingleCombo.clear();
    }
    vector<vector<WordSolution>> allWordCombinationsRefined;
    unsigned int properCombinationSize = 0;
    // O(c)
    for (unsigned int i = 0; i < constraints.size(); i++) {
        properCombinationSize += constraints[i].getFrequency();
    }
    // O(fCc/c)
    for (unsigned int i = 0; i < allWordCombinations.size(); i++) {
        if (allWordCombinations[i].size() == properCombinationSize) {
            allWordCombinationsRefined.push_back(allWordCombinations[i]);
        }
    }
    // saved refined word combinations
    allWordCombinations = allWordCombinationsRefined;
}

// check for duplicate boards by comparing their characters
// O(h*w)
bool sameAnswerGrid(const Puzzle& board1, const Puzzle& board2) {
    // O(h)
    for (unsigned int i = 0; i < board1.getRows(); i++) {
        // O(w)
        for (unsigned int j = 0; j < board1.getCols(); j++) {
            if (board1.getBoard()[i][j] != board2.getBoard()[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// throw out duplicate boards
// O((fCc)^3*h*w)
void removeDuplicateAnswerGrids(vector<Puzzle>& answerGrids) {
    if (answerGrids.size() > 1) {
        // O(fCc)
        for (unsigned int i = 0; i < answerGrids.size() - 1; i++) {
            // O(fCc)
            for (unsigned int j = i + 1; j < answerGrids.size(); j++) {
                // O(h*w)
                bool checkDuplicate = sameAnswerGrid(answerGrids[i],
                                                     answerGrids[j]);
                if (checkDuplicate) {
                    // erase duplicates
                    vector<Puzzle>::iterator itr = answerGrids.begin() + i;
                    // O(fCc)
                    answerGrids.erase(itr);
                }
            }
        }
    }
}

// throw out extraneous grids
// O(fCc*((d*h*w*(w + h) + f*log(f)) + fCc)
void removeExtraneousAnswerGrids(vector<Puzzle>& answerGrids,
                                 const vector<WordInput>& dictionaryWords) {
    bool erasedAlready = false;
    // O(fCc)
    for (unsigned int i = 0; i < answerGrids.size(); i++) {
        vector<WordSolution> wordsFound;
        // O(d*h*w*(w + h) + f*log(f))
        searchWords(answerGrids[i], dictionaryWords, wordsFound);
        // O(c)
        vector<WordSolution> promisedWords = answerGrids[i].getPromisedWords();
        promisedWords.clear();
        // if grids don't contain the words they are supposed to, discard them
        if (wordsFound.size() != answerGrids[i].getPromisedWords().size()) {
            vector<Puzzle>::iterator itr = answerGrids.begin() + i;
            // O(fCc)
            answerGrids.erase(itr);
            erasedAlready = true;
        }
        erasedAlready = false;
        wordsFound.clear();
    }
}

// check for invalid across words that are not present in the dictionary
// O(w)
bool searchAcrossInvalid(const Puzzle& grid, const vector<WordInput>&
                         dictionaryWords, unsigned int rowSearchIndex,
                         unsigned int colSearchIndex, string& currentWordAcross,
                         vector<Point>& searchedAcrossPath) {
    if (rowSearchIndex >= grid.getRows() || colSearchIndex >= grid.getCols() ||
        grid.getBoard()[rowSearchIndex][colSearchIndex] == '#') {
        // check word
        if (currentWordAcross.size() == 1) {
            return false;
        } else {
            for (unsigned int i = 0; i < dictionaryWords.size(); i++) {
                if (currentWordAcross == dictionaryWords[i].getWord()) {
                    return false;
                }
            }
            return true;
        }
    } else {
        // recurse until we hit the end of the board or a '#'
        searchedAcrossPath.push_back(Point(rowSearchIndex, colSearchIndex));
        currentWordAcross += grid.getBoard()[rowSearchIndex][colSearchIndex];
        return searchAcrossInvalid(grid, dictionaryWords, rowSearchIndex,
                    colSearchIndex + 1, currentWordAcross, searchedAcrossPath);
    }
}

// check for invalid down words that are not present in the dictionary
// O(h)
bool searchDownInvalid(const Puzzle& grid, const vector<WordInput>&
    dictionaryWords, unsigned int rowSearchIndex, unsigned int colSearchIndex,
                       string& currentWordDown, vector<Point>& searchedDownPath)
{
    if (rowSearchIndex >= grid.getRows() || colSearchIndex >= grid.getCols() ||
        grid.getBoard()[rowSearchIndex][colSearchIndex] == '#') {
        // check word
        if (currentWordDown.size() == 1) {
            return false;
        } else {
            for (unsigned int i = 0; i < dictionaryWords.size(); i++) {
                if (currentWordDown == dictionaryWords[i].getWord()) {
                    return false;
                }
            }
            return true;
        }
    } else {
        // recurse until we hit the end of the board or a '#'
        searchedDownPath.push_back(Point(rowSearchIndex, colSearchIndex));
        currentWordDown += grid.getBoard()[rowSearchIndex][colSearchIndex];
        return searchDownInvalid(grid, dictionaryWords, rowSearchIndex + 1,
                            colSearchIndex, currentWordDown, searchedDownPath);
    }
}

// keep across track of where we already checked for extraneous boards
// O(l)
bool alreadySearchedAcross(const vector<Point>& searchedAcrossPath,
                           unsigned int r, unsigned int c) {
    // O(l)
    for (unsigned int i = 0; i < searchedAcrossPath.size(); i++) {
        if (r == searchedAcrossPath[i].x && c == searchedAcrossPath[i].y) {
            return true;
        }
    }
    return false;
}

// keep down track of where we already checked for extraneous boards
// O(l)
bool alreadySearchedDown(const vector<Point>& searchedDownPath, unsigned int r,
                         unsigned int c) {
    // O(l)
    for (unsigned int i = 0; i < searchedDownPath.size(); i++) {
        if (r == searchedDownPath[i].x && c == searchedDownPath[i].y) {
            return true;
        }
    }
    return false;
}

// check for invalid words
// O(h*w*l^2*(w + h))
bool searchWordsInvalid(const Puzzle& grid, const vector<WordInput>&
                        dictionaryWords) {
    vector<Point> searchedAcrossPath;
    vector<Point> searchedDownPath;
    // O(h)
    for (unsigned int i = 0; i < grid.getRows(); i++) {
        // O(w)
        for (unsigned int j = 0; j < grid.getCols(); j++) {
            // O(l)
            if (grid.getBoard()[i][j] != '#') {
                string currentWordAcross = "";
                string currentWordDown = "";
                // call across invalid search to detect invalid across word
                // O(l)
                if (!alreadySearchedAcross(searchedAcrossPath, i, j)) {
                    // O(w)
                    if (searchAcrossInvalid(grid, dictionaryWords, i, j,
                                    currentWordAcross, searchedAcrossPath)) {
                        return true;
                    }
                }
                // call down invalid search to detect invalid down word
                // O(l)
                if (!alreadySearchedDown(searchedDownPath, i, j)) {
                    // O(h)
                    if (searchDownInvalid(grid, dictionaryWords, i, j,
                                          currentWordDown, searchedDownPath)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// throw out invalid answer grids containing words not in the dictionary
// O(fCc*(h*w*l^2*(w + h))
void removeInvalidAnswerGrids(vector<Puzzle>& answerGrids,
                              const vector<WordInput>& dictionaryWords) {
    vector<Puzzle> answerGridsRefined;
    // O(fCc)
    for (unsigned int i = 0; i < answerGrids.size(); i++) {
        // O(h*w*l^2*(w + h))
        if (!searchWordsInvalid(answerGrids[i], dictionaryWords)) {
            answerGridsRefined.push_back(answerGrids[i]);
        }
    }
    answerGrids = answerGridsRefined;
}

// create answer grids
// O(fCc*p + fCc*(l + h*w + c*log(c) + (fCc)^3*h*w + fCc*((d*h*w*(w + h) + f*log(f)) + fCc + fCc*(h*w*l^2*(w+h)))
void createAnswerGrids(const vector<vector<WordSolution>>& allWordCombinations,
    vector<Puzzle>& answerGrids, const Puzzle& grid, const vector<WordInput>&
                       dictionaryWords) {
    vector<vector<Point>> setOfPaths;
    vector<Point> path;
    // merge set of paths
    // O(fCc/c)
    for (unsigned int i = 0; i < allWordCombinations.size(); i++) {
        // O(c)
        for (unsigned int j = 0; j < allWordCombinations[i].size(); j++) {
            // O(p)
            path.insert(path.end(), allWordCombinations[i][j].getPath().begin(),
                        allWordCombinations[i][j].getPath().end());
        }
        setOfPaths.push_back(path);
        path.clear();
    }
    
    // replace characters not in solution words with '#' character
    // O(fCc)
    for (unsigned int counter = 0; counter < setOfPaths.size(); counter++) {
        vector<bool> col_bool(grid.getCols(), false);
        vector<vector<bool>> grid_bool(grid.getRows(), col_bool);
        vector<vector<char>> board = grid.getBoard();
        // O(l)
        for (unsigned int p = 0; p < setOfPaths[counter].size(); p++) {
            unsigned int x = setOfPaths[counter][p].x;
            unsigned int y = setOfPaths[counter][p].y;
            grid_bool[x][y] = true;
        }
        // O(h)
        for (unsigned int r = 0; r < grid_bool.size(); r++) {
            // O(w)
            for (unsigned int c = 0; c < grid_bool[r].size(); c++) {
                if (!grid_bool[r][c]) {
                    board[r][c] = '#';
                }
            }
        }
        Puzzle puzzleBoard(board);
        vector<WordSolution> promisedWords = allWordCombinations[counter];
        // O(c*log(c))
        sort(promisedWords.begin(), promisedWords.end(), wordLength);
        // O(1)
        puzzleBoard.initializePromisedWords(promisedWords);
        answerGrids.push_back(puzzleBoard);
        board.clear();
        promisedWords.clear();
    }
    
    // throw out erroneous answer grids
    // O((fCc)^3*h*w)
    removeDuplicateAnswerGrids(answerGrids);
    // O(fCc*((d*h*w*(w + h) + f*log(f)) + fCc)
    removeExtraneousAnswerGrids(answerGrids, dictionaryWords);
    // O(fCc*(h*w*l^2*(w + h))
    removeInvalidAnswerGrids(answerGrids, dictionaryWords);
}

// print solutions
// O(fCc*h*w)
void outputSolutions(const vector<Puzzle>& answerGrids, const string&
                     solution_mode, const string& output_mode) {
    bool noSolutions;
    if (answerGrids.size() == 0) {
        noSolutions = true;
    }
    // print_boards solution mode means print boards
    if (output_mode == "print_boards" && !noSolutions) {
        // print only one board for one_solution mode
        if (solution_mode == "one_solution") {
            cout << "Number of solution(s): " << 1 << endl;
            Puzzle currentGrid = answerGrids[0];
            for (unsigned int j = 0; j < currentGrid.getRows(); j++) {
                for (unsigned int k = 0; k < currentGrid.getCols(); k++) {
                    cout << currentGrid.getBoard()[j][k];
                }
                cout << endl;
            }
        } else if (solution_mode == "all_solutions") {
            // print all boards for all_solutions mode
            cout << "Number of solution(s): " << answerGrids.size() << endl;
            // O(fCc)
            for (unsigned int i = 0; i < answerGrids.size(); i++) {
                cout << "Board: " << endl;
                Puzzle currentGrid = answerGrids[i];
                // O(h)
                for (unsigned int j = 0; j < currentGrid.getRows(); j++) {
                    // O(w)
                    for (unsigned int k = 0; k < currentGrid.getCols(); k++) {
                        cout << currentGrid.getBoard()[j][k];
                    }
                    cout << endl;
                }
            }
        }
    } else if (output_mode == "count_only" || noSolutions) {
        // count_only solution mode means print only number of solutions
        cout << "Number of solution(s): " << answerGrids.size() << endl;
    }
}

int main(int argc, const char * argv[]) {
    // error checking to make sure correct number of arguments are supplied
    if (argc != 5 && argc != 6) {
        cerr << "Invalid number of command line arguments supplied.";
        cerr << "Only 4 or 5 arguments may be supplied." << endl;
        return 1;
    }
    // initializing input and output streams
    ifstream dictionary(argv[1]);
    ifstream puzzleInput(argv[2]);
    string solution_mode = string(argv[3]);
    string output_mode = string(argv[4]);
    string extra_credit_mode = "";
    vector<WordInput> dictionaryWords;
    vector<Constraint> constraints;
    vector<vector<char>> board;
    vector<WordSolution> wordsFound;
    vector<vector<WordSolution>> allWordCombinations;
    vector<Puzzle> answerGrids;
    // error checking to make sure command line arguments are valid
    if (argc == 6) {
        extra_credit_mode = string(argv[5]); 
    }
    if (solution_mode != string("one_solution") && solution_mode !=
        string("all_solutions")) {
        cerr << "Invalid argument for solution mode option" << endl;
        return 1;
    }
    if (output_mode != string("count_only") && output_mode !=
        string("print_boards")) {
        cerr << "Invalid argument for output mode option" << endl;
        return 1;
    }
    if (extra_credit_mode != string("gc") && extra_credit_mode != "") {
        cerr << "Invalid argument for extra credit option" << endl;
        return 1;
    }
    /*
     error checking to make sure that input file streams are working correctly
     for dictionary and input
     */
    if (!dictionary.good()) {
        cerr << "Unable to open and read crossword puzzle dictionary file: " <<
        argv[1] <<
        endl << endl;
        return 1;
    }
    if (!puzzleInput.good()) {
        cerr << "Unable to open and read crossword puzzle input file: " <<
        argv[1] <<
        endl << endl;
        return 1;
    }
    // run solver functions to generate crossword puzzle answers
    // O(d)
    parseDictionary(dictionary, dictionaryWords);
    // O((h + c + z)(c + w) + (c*log(c)))
    parsePuzzleInput(puzzleInput, constraints, board);
    if (constraints.size() == 0) {
        outputSolutions(answerGrids, solution_mode, output_mode);
    } else {
        Puzzle grid = board;
        // O(d*h*w*(w + h) + f*log(f))
        searchWords(grid, dictionaryWords, wordsFound);
        // O(c*fCc*x + (fCc)^2/(c^2)*log(fCc)
        findWordCombinations(constraints, wordsFound, allWordCombinations);
        // O(fCc*p + fCc*(l + h*w + c*log(c) + (fCc)^3*h*w + fCc*((d*h*w*(w + h) + f*log(f)) + fCc + fCc*(h*w*l^2*(w+h)))
        createAnswerGrids(allWordCombinations, answerGrids, grid,
                          dictionaryWords);
        // O(fCc*h*w)
        outputSolutions(answerGrids, solution_mode, output_mode);
    }
    return 0;
}
