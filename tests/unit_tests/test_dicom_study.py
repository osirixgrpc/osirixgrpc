import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import dcmpix_pb2
import dicomstudy_pb2
import types_pb2

class TestDicomStudy(GrpcTest):
    """Test case for DicomStudy messaging

    """
    def setUp(self):
        super().setUp()
        self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
        self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
        response = self.stub.DCMPixDicomImage(self.pix)
        self.dicom_image = response.dicom_image
        response = self.stub.DicomImageSeries(self.dicom_image)
        self.dicom_series = response.series
        response = self.stub.DicomSeriesStudy(self.dicom_series)
        self.dicom_study = response.study

    def testDicomStudyPaths(self):
        response = self.stub.DicomStudyPaths(self.dicom_study)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(len(response.paths) > 0)

    # def testDicomStudyImages(self):
    #     response = self.stub.DicomStudyImages(self.dicom_study)
    #     self.assertEqual(response.status.status, 1)
    #     self.assertTrue(isinstance(response.images[0], types_pb2.DicomImage))

    def testDicomStudyModlities(self):
        response = self.stub.DicomStudyModalities(self.dicom_study)

    def testDicomStudyNoFiles(self):
        response = self.stub.DicomStudyNoFiles(self.dicom_study)

    def testDicomStudyRawNoFiles(self):
        response = self.stub.DicomStudyRawNoFiles(self.dicom_study)

    def testDicomStudyNoFilesExcludingMultiFrames(self):
        response = self.stub.DicomStudyNoFilesExcludingMultiFrames(self.dicom_study)

    def testDicomStudyNumberOfImages(self):
        response = self.stub.DicomStudyNumberOfImages(self.dicom_study)

    def testDicomStudySeries(self):
        response = self.stub.DicomStudySeries(self.dicom_study)

    def testDicomStudyName(self):
        response = self.stub.DicomStudyName(self.dicom_study)

    def testDicomStudyDate(self):
        response = self.stub.DicomStudyDate(self.dicom_study)

    def testDicomStudyDateAdded(self):
        response = self.stub.DicomStudyDateAdded(self.dicom_study)

    def testDicomStudyDateOfBirth(self):
        response = self.stub.DicomStudyDateOfBirth(self.dicom_study)

    def testDicomStudyInstitutionName(self):
        response = self.stub.DicomStudyInstitutionName(self.dicom_study)

    def testDicomStudyModality(self):
        response = self.stub.DicomStudyModality(self.dicom_study)

    def testDicomStudyPatientID(self):
        response = self.stub.DicomStudyPatientID(self.dicom_study)

    def testDicomStudyPatientUID(self):
        response = self.stub.DicomStudyPatientUID(self.dicom_study)

    def testDicomStudyPatientSex(self):
        response = self.stub.DicomStudyPatientSex(self.dicom_study)

    def testDicomStudyPerformingPhysician(self):
        response = self.stub.DicomStudyPerformingPhysician(self.dicom_study)

    def testDicomStudyReferringPhysician(self):
        response = self.stub.DicomStudyReferringPhysician(self.dicom_study)

    def testDicomStudyStudyInstanceUID(self):
        response = self.stub.DicomStudyStudyInstanceUID(self.dicom_study)

    def testDicomStudyStudyName(self):
        response = self.stub.DicomStudyStudyName(self.dicom_study)
