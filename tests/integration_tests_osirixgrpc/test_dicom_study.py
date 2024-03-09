""" Test the osirixgrpc functionality for OsiriX DicomStudy class """

import os


def test_dicom_study_paths(grpc_stub, study_test):
    """ Check valid paths are returned """
    response = grpc_stub.DicomStudyPaths(study_test)
    assert response.status.status == 1, f"Could not request paths"
    paths = response.paths
    assert len(paths) == 40, f"Incorrect number of paths ({len(paths)})"
    for path in paths:
        assert os.path.exists(path), f"Path {path} does not exist"


def test_dicom_study_images(grpc_stub, study_test):
    """ Check that images are provided. """
    response = grpc_stub.DicomStudyImages(study_test)
    assert response.status.status == 1, f"Could not request images"
    images = response.images
    assert len(images) == 40, f"Bad number of images ({len(images)})"


def test_dicom_study_modalities(grpc_stub, study_test):
    """ Check correct modalities are provided. """
    response = grpc_stub.DicomStudyModalities(study_test)
    assert response.status.status == 1, f"Could not request modalities"
    assert response.modalities == "MR", f"Bad modalities {response.modalities}"


def test_dicom_study_modality(grpc_stub, study_test):
    """ Check correct modality is provided. """
    response = grpc_stub.DicomStudyModality(study_test)
    assert response.status.status == 1, f"Could not request modality"
    assert response.modality == "MR", f"Bad modalities {response.modality}"


def test_dicom_study_no_files(grpc_stub, study_test):
    """ Check no files is correctly provided. """
    response = grpc_stub.DicomStudyNoFiles(study_test)
    assert response.status.status == 1, f"Could not request no files"
    assert response.no_files == 40, f"Bad no files {response.no_files}"


def test_dicom_study_raw_no_files(grpc_stub, study_test):
    """ Check raw no files is correctly provided. """
    response = grpc_stub.DicomStudyRawNoFiles(study_test)
    assert response.status.status == 1, f"Could not request raw no files"
    assert response.no_files == 40, f"Bad raw no files {response.no_files}"