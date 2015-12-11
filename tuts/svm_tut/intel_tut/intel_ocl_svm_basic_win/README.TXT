------------------------------------------------------------------------------
                Intel(R) SDK for OpenCL(tm) Applications - Samples
                          Shared Virtual Memory Basic
                                    README
------------------------------------------------------------------------------

Introduction
------------------------------------------------------------------------------
This sample demonstrates the fundamentals of using Shared Virtual Memory (SVM)
capabilities in OpenCL(tm) applications. The SVM Basic code sample uses the
OpenCL 2.0 APIs to query SVM support and manage SVM allocations for the
selected OpenCL 2.0 device.

The sample package contains two similar implementations targeting different
SVM types each residing in a corresponding sub-folder:
  - coarse-grained buffer SVM (SVMBasicCoarseGrained directory);
  - fine-grained buffer SVM (SVMBasicFineGrained directory).

For more information about the sample, refer to the TutorialSVMBasic.pdf.

For complete list of supported operating systems and hardware, refer to the
release notes at the SDK website:
http://software.intel.com/en-us/vcsource/tools/opencl


Software Requirements
------------------------------------------------------------------------------
To correctly build and run the sample, the following is required:

  - Intel OpenCL 2.0 implementation for the target hardware set
  - Microsoft Visual Studio* version 2010 and higher
  - Intel SDK for OpenCL Applications 2014 and higher


Sample Directory Content
------------------------------------------------------------------------------
The sample directory contains the following:

  +--<sample_directory>
     |
     +-- common (directory with common utilities and helpers that are used as
     |           a basic infrastructure in the sample code)
     |
     +-- SVMBasicCoarseGrained (directory with the sample files targeting
     |                          coarse-grained buffer SVM type)
     |
     +-- SVMBasicFineGrained (directory with the sample files targeting
     |                        fine-grained buffer SVM type)
     |
     +-- templates (project property files)
     |
     +-- TutorialSVMBasic.pdf
     |
     +-- README.TXT


Building the Sample
------------------------------------------------------------------------------
The sample package contains the Microsoft Visual Studio solution files for
Visual Studio version 2010, 2012, and 2013.
To build the sample, do the following:

  1. Open the relevant solution file.
  2. In the Microsoft Visual Studio IDE select "Build" > "Build Solution".


Running the Sample
------------------------------------------------------------------------------
You can run the sample application using the standard interface of the
Microsoft Visual Studio.

To run the sample using the Visual Studio, do the following:

  1. Open and build the relevant solution file.
  2. Select a project file in the "Solution Explorer".
  3. Right-click the project and select "Set as StartUp Project".
  4. Press Ctrl+F5 to run the application.

To run the application in debug mode, press F5.


Disclaimer and Legal Information
------------------------------------------------------------------------------
THESE MATERIALS ARE PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR ITS
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THESE
MATERIALS, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

INFORMATION IN THIS DOCUMENT IS PROVIDED IN CONNECTION WITH INTEL
PRODUCTS. NO LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE,
TO ANY INTELLECTUAL PROPERTY RIGHTS IS GRANTED BY THIS DOCUMENT.
EXCEPT AS PROVIDED IN INTEL'S TERMS AND CONDITIONS OF SALE FOR SUCH
PRODUCTS, INTEL ASSUMES NO LIABILITY WHATSOEVER AND INTEL DISCLAIMS
ANY EXPRESS OR IMPLIED WARRANTY, RELATING TO SALE AND/OR USE OF INTEL
PRODUCTS INCLUDING LIABILITY OR WARRANTIES RELATING TO FITNESS FOR
A PARTICULAR PURPOSE, MERCHANTABILITY, OR INFRINGEMENT OF ANY PATENT,
COPYRIGHT OR OTHER INTELLECTUAL PROPERTY RIGHT.

A "Mission Critical Application" is any application in which failure
of the Intel Product could result, directly or indirectly, in personal
injury or death. SHOULD YOU PURCHASE OR USE INTEL'S PRODUCTS FOR ANY
SUCH MISSION CRITICAL APPLICATION, YOU SHALL INDEMNIFY AND HOLD INTEL
AND ITS SUBSIDIARIES, SUBCONTRACTORS AND AFFILIATES, AND THE DIRECTORS,
OFFICERS, AND EMPLOYEES OF EACH, HARMLESS AGAINST ALL CLAIMS COSTS,
DAMAGES, AND EXPENSES AND REASONABLE ATTORNEYS' FEES ARISING OUT OF,
DIRECTLY OR INDIRECTLY, ANY CLAIM OF PRODUCT LIABILITY, PERSONAL INJURY,
OR DEATH ARISING IN ANY WAY OUT OF SUCH MISSION CRITICAL APPLICATION,
WHETHER OR NOT INTEL OR ITS SUBCONTRACTOR WAS NEGLIGENT IN THE DESIGN,
MANUFACTURE, OR WARNING OF THE INTEL PRODUCT OR ANY OF ITS PARTS.

Intel may make changes to specifications and product descriptions at
any time, without notice. Designers must not rely on the absence or
characteristics of any features or instructions marked "reserved" or
"undefined". Intel reserves these for future definition and shall have
no responsibility whatsoever for conflicts or incompatibilities arising
from future changes to them. The information here is subject to change
without notice. Do not finalize a design with this information.

The products described in this document may contain design defects or
errors known as errata which may cause the product to deviate from
published specifications. Current characterized errata are available
on request.

Contact your local Intel sales office or your distributor to obtain the
latest specifications and before placing your product order.

Copies of documents which have an order number and are referenced in
this document, or other Intel literature, may be obtained
by calling 1-800-548-4725, or go to:
http://www.intel.com/design/literature.htm

Intel Corporation is the author of the Materials, and requests that all
problem reports or change requests be submitted to it directly.

Intel Core, HD Graphics and Iris Graphics are trademarks of Intel
Corporation in the U.S. and/or other countries.

* Other names and brands may be claimed as the property of others.

OpenCL and the OpenCL logo are trademarks of Apple Inc. used by
permission from Khronos.

Copyright (c) 2014 Intel Corporation. All rights reserved.