

#include "stdafx.h"

#include "BXL_Component.h"
#include "BXL_Decompress.h"
#include "BXL_Spirit.h"

#include "testing.h"

std::ofstream test_out("test.txt");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string get_blx_teststr();
std::ofstream bxl_decompress_os("test_decompress.txt");

extern const char* DIODE_SOT23_A_test;
extern const char* in_Lines;

#if 1
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	auto the_parser = Bridge::bxl;

	std::ifstream in(R"(.\test_files\MSP430G2253_PW_20.bxl)", std::ios::binary);

	//decompress the bxl file
	std::string bxl_text;
	BXLReader::Buffer reader( in );
	bxl_text = reader.decode_stream( );

	//visual dump
	{
		std::ofstream os("./bxl_output.txt");
		os.write(bxl_text.c_str(), bxl_text.size());
	}
	// parse into Component tho this may become an assembly
	std::cout << "\n\n" << "parse the BXL\n" << R"(.\test_files\MSP430G2253_PW_20.bxl)" << "\n\n";

	using namespace Bridge;
	using namespace boost::spirit::x3;

	Component::ComponentStore comp;
	auto begin = bxl_text.begin();
	bool r = phrase_parse(begin, end(bxl_text), the_parser, space, comp);
	//std::cout << std::boolalpha << "pass: " << r << std::endl;

//..............................
	//dump the compoment
	std::cout << "symbol: " << comp.symbol.name << std::endl;
	for (auto& i : comp.text_set)
		std::cout << i.first << " " << i.second.height << " " << i.second.width << std::endl;

	std::cout << '\n' << "pins:\n";
	for (auto& i : comp.symbol.pins)
		std::cout << i.number << " " << i.name << " " << i.name.name << std::endl;

	std::cout << '\n' << "draws:\n";
	for (auto& i : comp.symbol.draws)
	{
		//this only works because we know there are only lines in MSP430G2253_PW_20.bxl
		Line* pline = dynamic_cast<Line*>(i.get( ));
		std::cout << "a: " << pline->a << " b: " << pline->b << " width: " << pline->width << std::endl;
	}
	return 0;
}

#else

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	auto the_parser = Bridge::bxl;

	std::string bxl_text( DIODE_SOT23_A_test );

	std::cout << "\n\n" << "parse the BXL\n\n";

	using namespace Bridge;
	using namespace boost::spirit::x3;

	Component::ComponentStore comp;
	auto begin = bxl_text.begin();
	bool r = phrase_parse(begin, end(bxl_text), the_parser, space, comp);
	//std::cout << std::boolalpha << "pass: " << r << std::endl;

	//..............................
	//dump the compoment
	std::cout << std::endl << "dump:\n" << comp.symbol.name << "\n\ntext:\n";

	for (auto& i : comp.text_set)
		std::cout << i.first << " " << i.second.height << " " << i.second.width << std::endl;

	std::cout << '\n' << "pins:\n";
	for (auto& i : comp.symbol.pins)
		std::cout << "num: " << i.number << " name: " << i.name.name << " name_pos: " << i.name.pos << " text: " << i.designate.text_style << std::endl;

	std::cout << '\n' << "lines:\n";
	for (auto& i : comp.symbol.draws)
	{
		//this only works because we know there are only lines in MSP430G2253_PW_20.bxl
		Line* pline = dynamic_cast<Line*>(i.get());
		if (pline)
			std::cout << "line: " << pline->a << " b: " << pline->b << " width: " << pline->width << std::endl;
		Arcc* parc = dynamic_cast<Arcc*>(i.get());
		if (parc)
			std::cout << "arcc: " << parc->origin << "sa: " << parc->start_angle << " width: " << parc->width << std::endl;
	}
	std::cout << '\n' << "attributes:\n";
	for (auto& i : comp.symbol.attrs)
	{
		std::cout << i.name << std::endl;
	}
	return 0;
}
#endif

