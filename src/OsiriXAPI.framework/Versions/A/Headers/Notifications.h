/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

extern NSString* const OsiriXROISRName;
extern NSUInteger const OsiriXROISRID;

extern NSString* const OsiriXAnnotationSRName;
extern NSUInteger const OsiriXAnnotationSRID;

extern NSString* const OsiriXReportSRName;
extern NSUInteger const OsiriXReportSRID;

extern NSString* const OsiriXNoDeletionSRName;
extern NSUInteger const OsiriXNoDeletionSRID;

extern NSString* const OsiriXWindowsStateSRName;
extern NSUInteger const OsiriXWindowsStateSRID;

extern NSString* const OsirixViewerControllerPreviewMatrixRebuild;
extern NSString* const OsirixUpdateWLWWMenuNotification;
extern NSString* const OsirixChangeWLWWNotification;
extern NSString* const OsirixSync3DMPR;
extern NSString* const OsirixROICreateNotification;
extern NSString* const OsirixROIChangeNotification;
extern NSString* const OsirixCloseViewerNotification;
extern NSString* const OsirixUpdate2dCLUTMenuNotification;
extern NSString* const OsirixUpdate2dWLWWMenuNotification;
extern NSString* const OsirixLLMPRResliceNotification;
extern NSString* const OsirixROIVolumePropertiesChangedNotification;
extern NSString* const OsirixVRViewDidBecomeFirstResponderNotification;
extern NSString* const OsirixUpdateVolumeDataNotification;
extern NSString* const OsirixRevertSeriesNotification;
extern NSString* const OsirixOpacityChangedNotification;
extern NSString* const OsirixDefaultToolModifiedNotification;
extern NSString* const OsirixDefaultRightToolModifiedNotification;
extern NSString* const OsirixUpdateConvolutionMenuNotification;
extern NSString* const OsirixCLUTChangedNotification;
extern NSString* const OsirixUpdateCLUTMenuNotification;
extern NSString* const OsirixUpdateOpacityMenuNotification;
extern NSString* const OsirixRecomputeROINotification;
extern NSString* const OsirixStopPlayingNotification;
extern NSString* const OsirixChatBroadcastNotification;
extern NSString* const OsirixSyncSeriesNotification;
extern NSString* const OsirixOrthoMPRSyncSeriesNotification;
extern NSString* const OsirixReportModeChangedNotification;
extern NSString* const OsirixDeletedReportNotification;
extern NSString* const OsirixStudyAnnotationsChangedNotification;
extern NSString* const OsirixGLFontChangeNotification;
extern NSString* const OsirixDBHasBeenModifiedNotification;
extern NSString* const OsirixAddToDBNotification;
extern NSString* const OsirixAddToDBNotificationImagesIDsArray;
extern NSString* const OsirixAddToDBNotificationDICOMSRIDsArray;
extern NSString* const OsirixAddToDBNotificationNewStudiesIDsArray;
extern NSString* const OsirixAddToDBNotificationChangedSeriesIDsArray;
extern NSString* const OsirixDatabaseObjectsMayBecomeUnavailableNotification; // database objects may soon become invalid
extern NSString* const OsirixNewStudySelectedNotification;
extern NSString* const OsirixDidLoadNewObjectNotification;
extern NSString* const OsirixRTStructNotification;
extern NSString* const OsirixAlternateButtonPressedNotification;
extern NSString* const OsirixROISelectedNotification;
extern NSString* const OsirixRemoveROINotification;
extern NSString* const OsirixROIRemovedFromArrayNotification;
extern NSString* const OsirixViewOriginChanged;
extern NSString* const OsirixViewScaleChanged;
extern NSString* const OsirixChangeFocalPointNotification;
extern NSString* const OsirixWindow3dCloseNotification;
extern NSString* const OsirixDisplay3dPointNotification;
extern NSString* const OsirixPluginDownloadInstallDidFinishNotification;
extern NSString* const OsirixXMLRPCMessageNotification;
extern NSString* const OsirixDragMatrixImageMovedNotification;
extern NSString* const OsirixNotification;
extern NSString* const OsiriXFileReceivedNotification;
extern NSString* const OsirixDCMSendStatusNotification;
extern NSString* const OsirixStateChangedNotification;
extern NSString* const OsirixDCMUpdateCurrentImageNotification;
extern NSString* const OsirixDCMViewIndexChangedNotification;
extern NSString* const OsirixRightMouseUpNotification;
extern NSString* const OsirixMouseDownNotification;
extern NSString* const OsirixVRCameraDidChangeNotification;
extern NSString* const OsirixSyncNotification;
extern NSString* const OsirixOrthoMPRPosChangeNotification;
extern NSString* const OsirixAddROINotification;
extern NSString* const OsirixRightMouseDownNotification;
extern NSString* const OsirixRightMouseDraggedNotification;
extern NSString* const OsirixLabelGLFontChangeNotification;
extern NSString* const OsirixDrawTextInfoNotification;
extern NSString* const OsirixDrawObjectsNotification;
extern NSString* const OsirixDCMViewDidBecomeFirstResponderNotification;
extern NSString* const OsirixPerformDragOperationNotification;
extern NSString* const OsirixViewerWillChangeNotification;
extern NSString* const OsirixViewerDidChangeNotification;
extern NSString* const OsirixUpdateViewNotification;
extern NSString* const OsirixViewerControllerDidLoadImagesNotification;
extern NSString* const OsirixViewerControllerWillFreeVolumeDataNotification; // userinfo dict will contain an NSData with @"volumeData" key and a NSNumber with @"movieIndex" key
extern NSString* const OsirixViewerControllerDidAllocateVolumeDataNotification; // userinfo dict will contain an NSData with @"volumeData" key and a NSNumber with @"movieIndex" key
extern NSString* const OsiriXLogEvent;

extern NSString* const OsirixActiveLocalDatabaseDidChangeNotification;

extern NSString* const OsirixNodeRemovedFromCurvePathNotification;
extern NSString* const OsirixUpdateCurvedPathCostNotification;
extern NSString* const OsirixDeletedCurvedPathNotification;

/**
 * OsirixPopulatedContextualMenuNotification
 * object: NSMenu*
 * userInfo:
 *  - key [ViewerController className]
 *		the ViewerController the rightclick occurred in
 *	- key [ROI className], optional
 *		the rightclicked ROI
 **/
extern NSString* const OsirixPopulatedContextualMenuNotification;
