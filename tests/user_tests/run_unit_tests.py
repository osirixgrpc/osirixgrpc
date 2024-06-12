""" This script is used to run all unit tests within an OsiriX task """

import os
import shutil


class RunUnitTests:
    """ Used to run all unit tests within an OsiriX grpc task.

    All print statements should be visible within the OsiriXgrpc task manager.
    """
    @staticmethod
    def __working_directory__():
        """ The temporary directory where the code will be cloned and run from.
        """
        path = os.path.join(os.path.expanduser("~"), ".temp_osirix_test")
        os.makedirs(path, exist_ok=True)
        return path

    @staticmethod
    def __osirixgrpc_repo_url__():
        return "https://github.com/osirixgrpc/osirixgrpc.git"

    def __clone_repo__(self):
        os.system(f"git clone {self.__osirixgrpc_repo_url__()}")

    def run(self):
        # 1. Move to the working directory
        os.chdir(self.__working_directory__())

        # 2. Clone the osirixgrpc repository and move to dev branch
        self.__clone_repo__()
        os.chdir("osirixgrpc")
        os.system("git checkout dev")

        # 3. Run the unit tests
        os.chdir("tests")
        os.system("bash run_tests.sh")

        # 4. Remove the working directory
        shutil.rmtree(self.__working_directory__())


if __name__ == "__main__":
    rut = RunUnitTests()
    rut.run()
