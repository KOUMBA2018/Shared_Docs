#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

class show_copies {
    std::set<std::string> existing;
public:
    bool operator()(std::string const &in) {
        return existing.insert(in).second;
    }
};

void display( std::string src )
{
    std::cout << src << std::endl;
}

void removeDuplicates(std::vector<std::string> & liste) 
{ 
    int cpt=0; 
    bool bFound=false; 
    std::vector<std::string> final; 
    std::vector<std::string>::iterator iterListe, iterFinal; 
    std::set<std::string> result;

    
    std::remove_copy_if(liste.begin(), liste.end(),
    std::inserter(result, result.end()), show_copies());
    
    std::cout << std::endl;
    display("Duplicates words : ");

    for (auto const &s : result)
        display(s);
    
    if (liste.empty()) 
        return; 
    // Init of the result list  
    final.push_back(*liste.begin()); 
    for (iterListe=liste.begin()+1; iterListe!=liste.end(); iterListe++) 
    { 
        //Search if it is not a duplicate  
        bFound=false; 
        for (iterFinal=final.begin(); iterFinal!=final.end() && !bFound; iterFinal++) 
        { 
            if (0==iterListe->compare(*iterFinal)) 
            { 
                // It's a duplicate, we go to the next channel
                cpt++; 
                bFound=true; 
            } 
        } 
        if (!bFound) 
        { 
            // It is not a duplicate, we add it to the final list
            final.push_back(*iterListe); 
        } 
    } 
    liste=final; 
    return; 
}

std::vector<std::string> read_file( std::string const & fileName )
{
    std::vector< std::string > lines {};
    std::string line { "" };

    std::ifstream file { fileName };
    

    if ( !file )
    {
        throw std::runtime_error("File opening failed. Exiting program.\n");
    }

    while (std::getline( file, line ) )
    {
        lines.push_back( line );
    }

    return lines;
}

std::string ask_for_file_name()
{
    std::string file_name { "" };
    std::cout << "Enter a file name : ";
    std::cin >> file_name;

    return file_name;
}


int main()
{
    std::string file_name { ask_for_file_name() };
    bool valid_file  { true };
    int choice;

    do
    {
        try
        {
            auto lines = read_file( file_name );
            std::cout << std::endl;
            display("Initial list ");
            for ( auto const & line : lines )
            {
                display(line);
            }
            std::cout << std::endl;
            display("Choose the sorting mode, please(1:sort in alphabetical order or 2: sort in reverse alphabetical order)");
            
            std::cin >> choice;

            switch (choice)
            {   
                case 1:
                    display ("You have chosen the sort in alphabetical order !"); 
                    std::sort(std::begin(lines), std::end(lines));
                    break;
                case 2:
                    display("You have chosen the sort in reverse alphabetical order !"); 
                    std::sort(std::rbegin(lines), std::rend(lines));
                    break;
                case 1 xor 2:
                    display("You have chosen the two sort options !");
                    std::sort(std::begin(lines), std::end(lines));
                    std::sort(std::rbegin(lines), std::rend(lines));
                    break;
                default:
                    display("Your list could not be sorted !");
                    break;
            }

            removeDuplicates(lines); 
            std::cout << std::endl;
            display("sorted list and duplicates removed");
            for ( auto const & line : lines )
            {
                display(line);
            }
            valid_file = true;
        }
        catch ( std::runtime_error const & exception )
        {
            std::cout << "Error : " << exception.what() << std::endl;
            //If we reach this line, it means that an exception has been thrown because the name is not good. 
            valid_file = false;
            // So we ask for the name again.
            file_name = ask_for_file_name();
        }

    } while ( !valid_file );

    return 0;
}