import numpy as np

from grpc_test import GrpcTest
import utilities_pb2
import dcmpix_pb2
import dicomimage_pb2
import dicomseries_pb2
import dicomstudy_pb2
import viewercontroller_pb2
import types_pb2

class TestDCMPix(GrpcTest):
	"""Test case for ViewerController messaging

	"""
	def setUp(self):
		super().setUp()
		self.viewer_controller = self.stub.OsirixFrontmostViewer(utilities_pb2.Empty()).viewer_controller
		self.pix = self.stub.ViewerControllerCurDCM(self.viewer_controller).pix
		roi_request = viewercontroller_pb2.ViewerControllerROIsWithNameRequest(viewer_controller = self.viewer_controller, name = "test_grpc", movie_idx = 0)
		self.roi = self.stub.ViewerControllerROIsWithName(roi_request).rois[0]

	def testDCMPixConvertToRGB(self):
		request = dcmpix_pb2.DCMPixConvertToRGBRequest(pix = self.pix, rgb_channel = 3)
		response = self.stub.DCMPixConvertToRGB(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixConvertToBW(self):
		request = dcmpix_pb2.DCMPixConvertToBWRequest(pix = self.pix, bw_channel = 3)
		response = self.stub.DCMPixConvertToBW(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixIsRGB(self):
		response = self.stub.DCMPixIsRGB(self.pix)
		self.assertEqual(response.status.status, 1)

	def testDCMPixComputeROI(self):
		request = dcmpix_pb2.DCMPixComputeROIRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixComputeROI(request)
		self.assertEqual(response.status.status, 1)
        # TODO check these against a test ROI.

	def testDCMPixROIValues(self):
		request = dcmpix_pb2.DCMPixROIValuesRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixROIValues(request)
		self.assertEqual(response.status.status, 1)
		rows = np.array(response.row_indices)
		columns = np.array(response.column_indices)
		values = np.array(response.values)
        # TODO check these against a test dataset.

	def testDCMPixShape(self):
		response = self.stub.DCMPixShape(self.pix)
		self.assertEqual(response.status.status, 1)
		# TODO check these against a test dataset.

	def testDCMPixSpacing(self):
		response = self.stub.DCMPixSpacing(self.pix)
		self.assertEqual(response.status.status, 1)
		# TODO check these against a test dataset.

	def testDCMPixOrigin(self):
		response = self.stub.DCMPixOrigin(self.pix)
		self.assertEqual(response.status.status, 1)
		# TODO check these against a test dataset.

	def testDCMPixOrientation(self):
		response = self.stub.DCMPixOrientation(self.pix)
		self.assertEqual(response.status.status, 1)
		# TODO check these against a test dataset.

	def testDCMPixSliceLocation(self):
		response = self.stub.DCMPixSliceLocation(self.pix)
		self.assertEqual(response.status.status, 1)
		# TODO check these against a test dataset.

	def testDCMPixSourceFile(self):
		response = self.stub.DCMPixSourceFile(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertFalse(response.source_file == "")

	def testDCMPixImage(self):
		response = self.stub.DCMPixImage(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(response.rows > 0)
		self.assertTrue(response.columns > 0)
		if response.is_argb:
			self.assertEqual(len(response.image_data_argb), response.rows * response.columns * 4)
		else:
			self.assertEqual(len(response.image_data_float), response.rows * response.columns)

	def testDCMPixSetImage(self):
		response = self.stub.DCMPixImage(self.pix)
		if response.is_argb:
			request = dcmpix_pb2.DCMPixSetImageRequest(pix = self.pix, image_data_argb = response.image_data_argb)
		else:
			request = dcmpix_pb2.DCMPixSetImageRequest(pix = self.pix, image_data_float = response.image_data_float)
		response = self.stub.DCMPixSetImage(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixGetMapFromROI(self):
		request = dcmpix_pb2.DCMPixGetMapFromROIRequest(pix = self.pix, roi = self.roi)
		response = self.stub.DCMPixGetMapFromROI(request)
		self.assertEqual(response.status.status, 1)

	def testDCMPixDicomImage(self):
		response = self.stub.DCMPixDicomImage(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(isinstance(response.dicom_image, types_pb2.DicomImage))

	def testDCMPixDicomSeries(self):
		response = self.stub.DCMPixDicomSeries(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(isinstance(response.dicom_series, types_pb2.DicomSeries))

	def testDCMPixDicomStudy(self):
		response = self.stub.DCMPixDicomStudy(self.pix)
		self.assertEqual(response.status.status, 1)
		self.assertTrue(isinstance(response.dicom_study, types_pb2.DicomStudy))
