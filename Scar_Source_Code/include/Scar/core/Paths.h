#pragma once

#include <filesystem>
#include <string>

namespace Scar::Paths {
	namespace detail {
		inline bool Exists(const std::filesystem::path& path) {
			std::error_code error;
			return std::filesystem::exists(path, error);
		}

		inline bool IsRepositoryRoot(const std::filesystem::path& path) {
			return Exists(path / "Scar_Source_Code") && Exists(path / "PFE_Source_Code");
		}

		inline std::filesystem::path FindRepositoryRoot() {
			std::error_code error;
			auto current = std::filesystem::current_path(error);
			if (error) {
				return std::filesystem::path(".");
			}

			for (auto cursor = current; !cursor.empty(); cursor = cursor.parent_path()) {
				if (IsRepositoryRoot(cursor)) {
					return cursor;
				}

				if (cursor == cursor.root_path()) {
					break;
				}
			}

			return current;
		}
	}

	inline const std::filesystem::path& RepositoryRoot() {
		static const std::filesystem::path s_root = detail::FindRepositoryRoot();
		return s_root;
	}

	inline std::filesystem::path EngineShadersDir() {
		return RepositoryRoot() / "Scar_Source_Code" / "src" / "shaders";
	}

	inline std::filesystem::path EditorShadersDir() {
		return RepositoryRoot() / "PFE_Source_Code" / "src" / "shaders";
	}

	inline std::filesystem::path EditorAssetsDir() {
		return RepositoryRoot() / "PFE_Source_Code" / "assets";
	}

	inline std::filesystem::path EditorDesignsDir() {
		return RepositoryRoot() / "PFE_Source_Code" / "designs";
	}

	inline std::filesystem::path ResolveDesignPath(const std::filesystem::path& path) {
		return path.is_absolute() ? path : EditorDesignsDir() / path;
	}

	inline std::string ToString(const std::filesystem::path& path) {
		return path.lexically_normal().string();
	}
}
