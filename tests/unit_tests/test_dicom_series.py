import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import dcmpix_pb2
import dicomseries_pb2
import types_pb2

class TestDicomSeries(GrpcTest):
    """Test case for DicomSeries messaging

    """
    def setUp(self):
        super().setUp()
        self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
        self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
        response = self.stub.DCMPixDicomImage(self.pix)
        self.dicom_image = response.dicom_image
        response = self.stub.DicomImageSeries(self.dicom_image)
        self.dicom_series = response.series

    def testDicomSeriesPaths(self):
        response = self.stub.DicomSeriesPaths(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(len(response.paths) > 0)

    def testDicomSeriesPreviousSeries(self):
        response = self.stub.DicomSeriesPreviousSeries(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.previous_series, types_pb2.DicomSeries))

    def testDicomSeriesNextSeries(self):
        response = self.stub.DicomSeriesNextSeries(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.next_series, types_pb2.DicomSeries))

    def testDicomSeriesSortedImages(self):
        response = self.stub.DicomSeriesSortedImages(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.sorted_images[0], types_pb2.DicomImage))

    def testDicomSeriesStudy(self):
        response = self.stub.DicomSeriesStudy(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.study, types_pb2.DicomStudy))

    def testDicomSeriesImages(self):
        response = self.stub.DicomSeriesImages(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        self.assertTrue(isinstance(response.images[0], types_pb2.DicomImage))

    def testDicomSeriesSeriesInstanceUID(self):
        response = self.stub.DicomSeriesSeriesInstanceUID(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        # TODO - use real dataset to test.

    def testDicomSeriesSeriesSOPClassUID(self):
        response = self.stub.DicomSeriesSeriesSOPClassUID(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        # TODO - use real dataset to test.

    def testDicomSeriesSeriesDescription(self):
        response = self.stub.DicomSeriesSeriesDescription(self.dicom_series)
        # TODO - use real dataset to test.
        # Make sure a series description is available in the dataset

    def testDicomSeriesModality(self):
        response = self.stub.DicomSeriesModality(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        # TODO - use real dataset to test.

    def testDicomSeriesName(self):
        response = self.stub.DicomSeriesName(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        # TODO - use real dataset to test.

    def testDicomSeriesDate(self):
        response = self.stub.DicomSeriesDate(self.dicom_series)
        self.assertEqual(response.status.status, 1)
        # TODO - use real dataset to test.
