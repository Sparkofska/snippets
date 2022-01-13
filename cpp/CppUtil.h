// get the underlying value of en enum
template <typename Enumeration>
auto valueOf(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}
