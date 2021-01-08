/*
 * TAR File-system Driver Header File
 * SKELETON IMPLEMENTATION -- TO BE FILLED IN FOR TASK (4)
 */

/*
 * STUDENT NUMBER: s
 */
#ifndef TARFS_H
#define TARFS_H

#include <infos/fs/block-based-filesystem.h>
#include <infos/fs/pfs-node.h>
#include <infos/fs/file.h>
#include <infos/fs/directory.h>

#include <infos/drivers/block/block-device.h>

#include <infos/util/string.h>
#include <infos/util/map.h>
#include <infos/util/list.h>

namespace tarfs {

	class TarFSNode;
	class TarFSFile;

	struct posix_header;

	class TarFS : public infos::fs::BlockBasedFilesystem {
		friend class TarFSNode;
		friend class TarFSFile;

	public:

		TarFS(infos::drivers::block::BlockDevice& bdev) : BlockBasedFilesystem(bdev), _root_node(NULL) {
		}

		infos::fs::PFSNode *mount() override;

		const infos::util::String name() const {
			return "tarfs";
		}

	private:
		TarFSNode *build_tree();
		
		static bool is_zero_block(const uint8_t *buffer, size_t size = 512) {
			for (unsigned int i = 0; i < size; i++) {
				if (buffer[i] != 0) return false;
			}

			return true;
		}

		TarFSNode *_root_node;
	};

	class TarFSFile : public infos::fs::File {
	public:

		TarFSFile(TarFS& owner, unsigned int file_header_block);
		virtual ~TarFSFile();

		void close() override;

		int read(void* buffer, size_t size) override;
		int pread(void* buffer, size_t size, off_t off) override;

		int write(const void* buffer, size_t size) override {
			// DO NOT IMPLEMENT
			return 0;
		}

		void seek(off_t offset, SeekType type) override;
		
		unsigned int size() const;

	private:
		struct posix_header *_hdr;

		TarFS& _owner;
		unsigned int _file_start_block, _cur_pos;
	};

	class TarFSDirectory : public infos::fs::Directory {
	public:
		TarFSDirectory(TarFSNode& node);
		virtual ~TarFSDirectory();

		bool read_entry(infos::fs::DirectoryEntry& entry) override;
		void close() override;

	private:
		infos::fs::DirectoryEntry *_entries;
		unsigned int _nr_entries, _cur_entry;
	};

	class TarFSNode : public infos::fs::PFSNode {
	public:
		typedef infos::util::Map<infos::util::String::hash_type, TarFSNode *> TarFSNodeMap;

		TarFSNode(TarFSNode *parent, const infos::util::String& name, TarFS& owner);
		virtual ~TarFSNode();

		infos::fs::File* open() override;
		infos::fs::Directory* opendir() override;

		PFSNode* get_child(const infos::util::String& name) override;

		PFSNode* mkdir(const infos::util::String& name) override;

		void set_block_offset(unsigned int offset);

		void add_child(const infos::util::String& name, TarFSNode *child);

		const TarFSNodeMap& children() const {
			return _children;
		}

		const infos::util::String& name() const {
			return _name;
		}

		unsigned int size() const {
			return _size;
		}

		void size(unsigned int size) {
			_size = size;
		}

	private:
		TarFSNodeMap _children;
		const infos::util::String _name;
		unsigned int _size;
		bool _has_block_offset;
		unsigned int _block_offset;
	};
}

#endif /* TARFS_H */

