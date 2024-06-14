<!-- Choose a short, distinct and distinctive name for your script.  Should match name of parent directory -->
# Template

<!-- shortdesc --> A script for importing and visualizing ITK images (e.g. nrrd, mhd/mha, nifti) within OsiriX. 

<!-- Choose the relevant categories out of "Database-blue", "Image-green", "ROI-purple" or "VR-red" -->
__Categories__:
![Database](https://img.shields.io/badge/Database-blue)

<!-- Do not modify. Source image must have size 800 x 600 pixels. -->
<div style="text-align: center;">
<img alt="Script screenshot" height="300" src="screenshot.png" width="400" style="border: 1px solid grey;"/>
</div>

<!-- 
Please ensure that you (and your institution) get acknowledgment for your contribution!
Multiple entries should be comma-separated.
-->
## Authors
<table>
  <tr>
    <td> <b>Author(s)</b> </td>
    <td> Matthew Blackledge<sup>1</sup> </td>
  </tr>
  <tr>
    <td> <b>Institution(s)</b> </td>
    <td> <sup>1</sup>The Institute of Cancer Research </td>
  </tr>
  <tr>
    <td> <b>Contact</b> </td>
    <td> matthew.blackledge@icr.ac.uk </td>
  </tr>
</table>

## Datasets
Any data.

## Details
This script will read an ITK image format, create basic Dicom files, and load them into OsiriX for viewing. 
Note that all created Dicom files will have SOP class "Secondary Capture Image" by default. Please change the relevant
line in the code `ds.SOPClassUID = "1.2.840.10008.5.1.4.1.1.7"` to the necessary image type if required.
Each ITK image will have a unique series and study UID.

### Expected Outcome
Should load the ITK image into the OsiriX database for visualization.