std::vector<std::string> split(std::string s, std::string delimiter);
std::string removeAllWhitespace(std::string& str);
bool endsWith(const std::string& str, const std::string& suffix);
bool startsWith(const std::string& str, const std::string& prefix);

// The Levenshtein distance is a string metric for measuring the difference between two sequences.
unsigned int calcLevenshteinDistance(const std::string& s1, const std::string& s2);

// Clamp string length and append "..." if longer than given max length.
std::string abbreviate(const std::string& str, const int maxLength = 10);

// Implode many strings to one long string with delimiter.
std::string join(const std::vector<std::string>& parts, const std::string& delimiter = ",");

std::string tolower(const std::string& str);

bool equalsIgnoreCase(const std::string& str1, const std::string& str2);
