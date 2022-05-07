import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import dcmpix_pb2
import dicomimage_pb2
import types_pb2

class TestDicomImage(GrpcTest):
    """Test case for DicomImage messaging

    """
    def setUp(self):
        super().setUp()
        self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
        self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
        response = self.stub.DCMPixDicomImage(self.pix)
        self.dicom_image = response.dicom_image

    def testDicomImageWidth(self):
        response = self.stub.DicomImageWidth(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known width given test data

    def testDicomImageHeight(self):
        response = self.stub.DicomImageHeight(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known height given test data

    def testDicomImageSOPInstanceUID(self):
        response = self.stub.DicomImageSOPInstanceUID(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known SOP instance given test data

    def testDicomImageCompletePath(self):
        response = self.stub.DicomImageCompletePath(self.dicom_image)
        self.assertEqual(response.status.status, 1)

    def testDicomImageDate(self):
        response = self.stub.DicomImageDate(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known date given test data

    def testDicomImageNumberOfFrames(self):
        response = self.stub.DicomImageNumberOfFrames(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known # frames given test data

    def testDicomImageModality(self):
        response = self.stub.DicomImageModality(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known modality given test data

    def testDicomImageSeries(self):
        response = self.stub.DicomImageSeries(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.series, types_pb2.DicomSeries))

    def testDicomImageSliceLocation(self):
        response = self.stub.DicomImageSliceLocation(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known slice location given test data

    def testDicomImageInstanceNumber(self):
        response = self.stub.DicomImageInstanceNumber(self.dicom_image)
        self.assertEqual(response.status.status, 1)
        # TODO - check against a known instance number given test data
