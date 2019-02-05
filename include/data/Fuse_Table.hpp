#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "data/Fuse_Object.hpp"

namespace Fuse {

	class Table : Object {
	public:
		Table();
	
		Table* Clone(); // returns a clone of the table
		
		std::string ToString();
		
		std::size_t Count();
		std::shared_ptr<Object> Access(std::size_t index);
		std::shared_ptr<Object> Access(const std::string& key);
		
		/* Erases element at index or a key, returns 1 for success
		   0 for error */
		int Erase(std::size_t index);
		int Erase(const std::string& key);
		
		void AddEntry(Object*);
		void AddKey(Object*, const std::string& key);
	private:
		Type type = TYPE_TABLE;
		std::vector< std::shared_ptr<Object> > data;
		std::map< std::string , std::shared_ptr<Object> > dict;
	};

};