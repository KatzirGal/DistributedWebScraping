import subprocess
import os
import sys
import argparse
import platform
import shutil

def is_unix_environment():
    """Check if the script is running on a Unix-like system."""
    return platform.system() != "Windows"

def run_command(command, cwd=None):
    try:
        result = subprocess.run(command, cwd=cwd, check=True, shell=True, text=True, stdout=sys.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Error while executing command: {e.cmd}")
        print(e.stderr)
        sys.exit(1)

def main():
    parser = argparse.ArgumentParser(description="Build using CMake.")
    parser.add_argument("--config", choices=["Release", "Debug", "RelWithDebInfo"], default="Release", help="Build configuration (default: Release)")
    args = parser.parse_args()

    cmake_build_folder = "CMAKE_BUILD"

    # Create build directory
    os.makedirs(cmake_build_folder, exist_ok=True)

    print("Running CMake to generate the project...")
    if is_unix_environment():
        def find_unix_compiler():
            for compiler in ['g++-13']:
                if shutil.which(compiler):
                    return shutil.which(compiler)
            raise RuntimeError("No suitable compiler found (Should be g++-13)")
        unix_compiler = find_unix_compiler()

        poco_cmake_dir = os.path.abspath(f'Dependencies/Poco/CMAKE_BUILD/install/{args.config}/lib/cmake/Poco')
        
        run_command(f'cmake -B {cmake_build_folder} -G "Unix Makefiles" -DCMAKE_BUILD_TYPE={args.config} -DCMAKE_CXX_COMPILER={unix_compiler} -DCMAKE_PREFIX_PATH={poco_cmake_dir} -DPoco_DIR={poco_cmake_dir} -DPocoFoundation_DIR={poco_cmake_dir}', cwd='Dependencies/Poco')
        run_command(f'cmake --build {cmake_build_folder} --config {args.config} --target Poco', cwd='Dependencies/Poco')
        run_command(f'cmake -B {cmake_build_folder} -G "Unix Makefiles" -DCMAKE_BUILD_TYPE={args.config} -DCMAKE_CXX_COMPILER={unix_compiler} -DCMAKE_PREFIX_PATH={poco_cmake_dir} -DPoco_DIR={poco_cmake_dir} -DPocoFoundation_DIR={poco_cmake_dir}')
    else:
        print("Configuring CMake to use Boost and OpenSSL...")

        boost_install_dir = os.path.abspath(f'Dependencies/boost/CMAKE_BUILD/install/{args.config}')
        boost_cmake_dir = os.path.join(boost_install_dir, "lib", "cmake", "Boost-1.83.0")

        openssl_root = "C:/OpenSSL-Win64"
        openssl_include = os.path.join(openssl_root, "include").replace('\\', '/')

        run_command(f'cmake -B {cmake_build_folder} -S . -G "Visual Studio 17 2022" -A x64 '
                    f'-DCMAKE_BUILD_TYPE={args.config} '
                    f'-DBoost_DIR="{boost_cmake_dir}" '
                    f'-DCMAKE_PREFIX_PATH="{boost_cmake_dir};{openssl_root};C:/OpenSSL-Win64/lib/VC/x64/MDd" '
                    f'-DOPENSSL_ROOT_DIR="{openssl_root}" '
                    f'-DOPENSSL_INCLUDE_DIR="{openssl_include}" '
                    f'-DOPENSSL_USE_STATIC_LIBS=TRUE '
                    f'-DOPENSSL_CRYPTO_LIBRARY="{openssl_root}/lib/VC/x64/MDd/libcrypto_staticd.lib" '
                    f'-DOPENSSL_SSL_LIBRARY="{openssl_root}/lib/VC/x64/MDd/libssl_staticd.lib" '
                    f'-DOPENSSL_LIBRARIES="{openssl_root}/lib/VC/x64/MDd/libssl_staticd.lib;{openssl_root}/lib/VC/x64/MDd/libcrypto_staticd.lib" '
                    f'-DCMAKE_REQUIRED_LIBRARIES="{openssl_root}/lib/VC/x64/MDd/libssl_staticd.lib;{openssl_root}/lib/VC/x64/MDd/libcrypto_staticd.lib"'
                    f'-DOPENSSL_NO_DEFAULT_PATH=TRUE'
                    )



    # Step 2: Call cmake --build
    print("Building the project using CMake...")
    run_command(f'cmake --build {cmake_build_folder} --config {args.config}')

    build_folder = "build" if is_unix_environment() else f'x64\\{args.config}'

    print("\nBuild complete!")
    print("To execute the application, use the following command:")
    print(f'/{build_folder}/Orchestrator' if is_unix_environment() else f'{build_folder}\\Orchestrator.exe')

if __name__ == "__main__":
    main()
