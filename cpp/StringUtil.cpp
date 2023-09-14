std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

std::string removeAllWhitespace(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) {return std::isspace(c); }), str.end());
	return str;
}

bool endsWith(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool startsWith(const std::string& str, const std::string& prefix)
{
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

unsigned int calcLevenshteinDistance(const std::string& s1, const std::string& s2)
{
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for (unsigned int i = 1; i <= len1; ++i)
		for (unsigned int j = 1; j <= len2; ++j)
			// note that std::min({arg1, arg2, arg3}) works only in C++11,
			// for C++98 use std::min(std::min(arg1, arg2), arg3)
			d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
	return d[len1][len2];
}

std::string StringUtil::abbreviate(const std::string& str, const int maxLength /*= 10*/)
{
	if (str.length() > maxLength)
		return str.substr(0, maxLength) + "...";

	return str;
}

std::string StringUtil::join(const std::vector<std::string>& parts, const std::string& delimiter /*= ","*/)
{
	if (parts.empty())
		return "";

	return std::accumulate(
		std::next(parts.begin()),
		parts.end(),
		parts[0],
		[&](const std::string& a, const std::string& b) { return a + delimiter + b; }
	);
}

std::string tolower(const std::string& str)
{
	std::string lower = str;
	std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
	return lower;
}

bool equalsIgnoreCase(const std::string& str1, const std::string& str2)
{
	return tolower(str1).compare(tolower(str2)) == 0;
}

std::string StringUtils::replace(const std::string &original, const std::string &search, const std::string &replace, int count /*= -1*/)
{
	std::string result = original; // Create a copy of the original string
	size_t startPos = 0;
	int replacements = 0;

	while (count != 0 && (startPos = result.find(search, startPos)) != std::string::npos)
	{
		result.replace(startPos, search.length(), replace);
		startPos += replace.length();
		++replacements;
		if (count > 0 && replacements >= count)
		{
			break;
		}
	}

	return result;
}

void StringUtil::ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

void StringUtil::rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void StringUtil::trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

std::string StringUtil::ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}

std::string StringUtil::rtrim_copy(std::string s)
{
	rtrim(s);
	return s;
}

std::string StringUtil::trim_copy(std::string s)
{
	trim(s);
	return s;
}
