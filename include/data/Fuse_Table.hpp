#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "data/Fuse_Object.hpp"

namespace Fuse {

	class Table : public Object {
	public:
		Table();
	
		Type GetType();
	
		std::shared_ptr<Object> Clone(); // returns a clone of the table
		
		std::string ToString();
		
		std::size_t Count();
		std::shared_ptr<Fuse::Object> Access(std::size_t index);
		std::shared_ptr<Fuse::Object> Access(const std::string& key);
		std::shared_ptr<Fuse::Object> Assign(std::size_t index, std::shared_ptr<Object> obj);
		std::shared_ptr<Fuse::Object> Assign(const std::string& key, std::shared_ptr<Object> obj);
		
		/* Erases element at index or a key, returns 1 for success
		   0 for error */
		int Erase(std::size_t index);
		int Erase(const std::string& key);
		
		void AddEntry(std::shared_ptr<Object>);
		void AddKey(std::shared_ptr<Object>, const std::string& key);
		bool IsTrue();
	private:
		std::vector< std::shared_ptr< std::shared_ptr<Object> > > data;
		std::map< std::string , std::shared_ptr< std::shared_ptr<Object> > > dict;
	};

};