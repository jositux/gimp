# The GIMP -- an image manipulation program
# Copyright (C) 1999 Manish Singh <yosh@gimp.org>

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUTFILE ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# autogenerated by enumgen.pl

package Gimp::CodeGen::enums;

%enums = (
    MessageHandlerType =>
	{ contig => 1,
	  header => 'appenv.h',
	  symbols => [ qw(MESSAGE_BOX CONSOLE ERROR_CONSOLE) ],
	  mapping => { MESSAGE_BOX => '0',
		       CONSOLE => '1',
		       ERROR_CONSOLE => '2' }
	},
    GimpImageBaseType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(RGB GRAY INDEXED) ],
	  mapping => { RGB => '0',
		       GRAY => '1',
		       INDEXED => '2' }
	},
    GimpImageType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(RGB_GIMAGE RGBA_GIMAGE GRAY_GIMAGE GRAYA_GIMAGE
			  INDEXED_GIMAGE INDEXEDA_GIMAGE) ],
	  mapping => { RGB_GIMAGE => '0',
		       RGBA_GIMAGE => '1',
		       GRAY_GIMAGE => '2',
		       GRAYA_GIMAGE => '3',
		       INDEXED_GIMAGE => '4',
		       INDEXEDA_GIMAGE => '5' },
	  nicks   => { RGB_GIMAGE => 'RGB_IMAGE',
		       RGBA_GIMAGE => 'RGBA_IMAGE',
		       GRAY_GIMAGE => 'GRAY_IMAGE',
		       GRAYA_GIMAGE => 'GRAYA_IMAGE',
		       INDEXED_GIMAGE => 'INDEXED_IMAGE',
		       INDEXEDA_GIMAGE => 'INDEXEDA_IMAGE' }
	},
    GimpFillType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(FOREGROUND_FILL BACKGROUND_FILL WHITE_FILL
			  TRANSPARENT_FILL NO_FILL) ],
	  mapping => { FOREGROUND_FILL => '0',
		       BACKGROUND_FILL => '1',
		       WHITE_FILL => '2',
		       TRANSPARENT_FILL => '3',
		       NO_FILL => '4' },
	  nicks   => { FOREGROUND_FILL => 'FG_IMAGE_FILL',
		       BACKGROUND_FILL => 'BG_IMAGE_FILL',
		       WHITE_FILL => 'WHITE_IMAGE_FILL',
		       TRANSPARENT_FILL => 'TRANS_IMAGE_FILL',
		       NO_FILL => 'NO_IMAGE_FILL' }
	},
    LayerModeEffects =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(NORMAL_MODE DISSOLVE_MODE BEHIND_MODE
			  MULTIPLY_MODE SCREEN_MODE OVERLAY_MODE
			  DIFFERENCE_MODE ADDITION_MODE SUBTRACT_MODE
			  DARKEN_ONLY_MODE LIGHTEN_ONLY_MODE HUE_MODE
			  SATURATION_MODE COLOR_MODE VALUE_MODE DIVIDE_MODE) ],
	  mapping => { NORMAL_MODE => '0',
		       DISSOLVE_MODE => '1',
		       BEHIND_MODE => '2',
		       MULTIPLY_MODE => '3',
		       SCREEN_MODE => '4',
		       OVERLAY_MODE => '5',
		       DIFFERENCE_MODE => '6',
		       ADDITION_MODE => '7',
		       SUBTRACT_MODE => '8',
		       DARKEN_ONLY_MODE => '9',
		       LIGHTEN_ONLY_MODE => '10',
		       HUE_MODE => '11',
		       SATURATION_MODE => '12',
		       COLOR_MODE => '13',
		       VALUE_MODE => '14',
		       DIVIDE_MODE => '15' }
	},
    ConvolutionType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(NORMAL_CONVOL ABSOLUTE_CONVOL NEGATIVE_CONVOL) ],
	  mapping => { NORMAL_CONVOL => '0',
		       ABSOLUTE_CONVOL => '1',
		       NEGATIVE_CONVOL => '2' }
	},
    BrushApplicationMode =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(HARD SOFT PRESSURE) ],
	  mapping => { HARD => '0',
		       SOFT => '1',
		       PRESSURE => '2' }
	},
    PaintApplicationMode =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(CONSTANT INCREMENTAL) ],
	  mapping => { CONSTANT => '0',
		       INCREMENTAL => '1' },
	  nicks   => { CONSTANT => 'CONTINUOUS' }
	},
    MaskApplyMode =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(APPLY DISCARD) ],
	  mapping => { APPLY => '0',
		       DISCARD => '1' }
	},
    AddMaskType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(ADD_WHITE_MASK ADD_BLACK_MASK ADD_ALPHA_MASK) ],
	  mapping => { ADD_WHITE_MASK => '0',
		       ADD_BLACK_MASK => '1',
		       ADD_ALPHA_MASK => '2' },
	  nicks   => { ADD_WHITE_MASK => 'WHITE_MASK',
		       ADD_BLACK_MASK => 'BLACK_MASK',
		       ADD_ALPHA_MASK => 'ALPHA_MASK' }
	},
    GradientPaintMode =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(ONCE_FORWARD ONCE_BACKWARDS LOOP_SAWTOOTH
			  LOOP_TRIANGLE ONCE_END_COLOR) ],
	  mapping => { ONCE_FORWARD => '0',
		       ONCE_BACKWARDS => '1',
		       LOOP_SAWTOOTH => '2',
		       LOOP_TRIANGLE => '3',
		       ONCE_END_COLOR => '4' }
	},
    InterpolationType =>
	{ contig => 1,
	  header => 'apptypes.h',
	  symbols => [ qw(LINEAR_INTERPOLATION CUBIC_INTERPOLATION
			  NEAREST_NEIGHBOR_INTERPOLATION) ],
	  mapping => { LINEAR_INTERPOLATION => '0',
		       CUBIC_INTERPOLATION => '1',
		       NEAREST_NEIGHBOR_INTERPOLATION => '2' }
	},
    GradientType =>
	{ contig => 1,
	  header => 'blend.h',
	  symbols => [ qw(LINEAR BILINEAR RADIAL SQUARE CONICAL_SYMMETRIC
			  CONICAL_ASYMMETRIC SHAPEBURST_ANGULAR
			  SHAPEBURST_SPHERICAL SHAPEBURST_DIMPLED
			  SPIRAL_CLOCKWISE SPIRAL_ANTICLOCKWISE) ],
	  mapping => { LINEAR => '0',
		       BILINEAR => '1',
		       RADIAL => '2',
		       SQUARE => '3',
		       CONICAL_SYMMETRIC => '4',
		       CONICAL_ASYMMETRIC => '5',
		       SHAPEBURST_ANGULAR => '6',
		       SHAPEBURST_SPHERICAL => '7',
		       SHAPEBURST_DIMPLED => '8',
		       SPIRAL_CLOCKWISE => '9',
		       SPIRAL_ANTICLOCKWISE => '10' }
	},
    BlendMode =>
	{ contig => 1,
	  header => 'blend.h',
	  symbols => [ qw(FG_BG_RGB_MODE FG_BG_HSV_MODE FG_TRANS_MODE
			  CUSTOM_MODE) ],
	  mapping => { FG_BG_RGB_MODE => '0',
		       FG_BG_HSV_MODE => '1',
		       FG_TRANS_MODE => '2',
		       CUSTOM_MODE => '3' },
	  nicks   => { FG_BG_RGB_MODE => 'FG_BG_RGB',
		       FG_BG_HSV_MODE => 'FG_BG_HSV',
		       FG_TRANS_MODE => 'FG_TRANS',
		       CUSTOM_MODE => 'CUSTOM' }
	},
    RepeatMode =>
	{ contig => 1,
	  header => 'blend.h',
	  symbols => [ qw(REPEAT_NONE REPEAT_SAWTOOTH REPEAT_TRIANGULAR) ],
	  mapping => { REPEAT_NONE => '0',
		       REPEAT_SAWTOOTH => '1',
		       REPEAT_TRIANGULAR => '2' }
	},
    BucketFillMode =>
	{ contig => 1,
	  header => 'bucket_fill.h',
	  symbols => [ qw(FG_BUCKET_FILL BG_BUCKET_FILL PATTERN_BUCKET_FILL) ],
	  mapping => { FG_BUCKET_FILL => '0',
		       BG_BUCKET_FILL => '1',
		       PATTERN_BUCKET_FILL => '2' }
	},
    ChannelOps =>
	{ contig => 1,
	  header => 'channel.h',
	  symbols => [ qw(ADD SUB REPLACE INTERSECT) ],
	  mapping => { ADD => '0',
		       SUB => '1',
		       REPLACE => '2',
		       INTERSECT => '3' }
	},
    ChannelOffsetType =>
	{ contig => 1,
	  header => 'channel_ops.h',
	  symbols => [ qw(OFFSET_BACKGROUND OFFSET_TRANSPARENT) ],
	  mapping => { OFFSET_BACKGROUND => '0',
		       OFFSET_TRANSPARENT => '1' }
	},
    CloneType =>
	{ contig => 1,
	  header => 'clone.h',
	  symbols => [ qw(IMAGE_CLONE PATTERN_CLONE) ],
	  mapping => { IMAGE_CLONE => '0',
		       PATTERN_CLONE => '1' }
	},
    TransferMode =>
	{ contig => 1,
	  header => 'color_balance.h',
	  symbols => [ qw(SHADOWS MIDTONES HIGHLIGHTS) ],
	  mapping => { SHADOWS => '0',
		       MIDTONES => '1',
		       HIGHLIGHTS => '2' }
	},
    ConvertPaletteType =>
	{ contig => 1,
	  header => 'convert.h',
	  symbols => [ qw(MAKE_PALETTE REUSE_PALETTE WEB_PALETTE
			  MONO_PALETTE CUSTOM_PALETTE) ],
	  mapping => { MAKE_PALETTE => '0',
		       REUSE_PALETTE => '1',
		       WEB_PALETTE => '2',
		       MONO_PALETTE => '3',
		       CUSTOM_PALETTE => '4' }
	},
    ConvertDitherType =>
	{ contig => 1,
	  header => 'convert.h',
	  symbols => [ qw(NO_DITHER FS_DITHER FSLOWBLEED_DITHER FIXED_DITHER
			  NODESTRUCT_DITHER) ],
	  mapping => { NO_DITHER => '0',
		       FS_DITHER => '1',
		       FSLOWBLEED_DITHER => '2',
		       FIXED_DITHER => '3',
		       NODESTRUCT_DITHER => '4' }
	},
    ConvolveType =>
	{ contig => 1,
	  header => 'convolve.h',
	  symbols => [ qw(BLUR_CONVOLVE SHARPEN_CONVOLVE CUSTOM_CONVOLVE) ],
	  mapping => { BLUR_CONVOLVE => '0',
		       SHARPEN_CONVOLVE => '1',
		       CUSTOM_CONVOLVE => '2' }
	},
    DodgeBurnType =>
	{ contig => 1,
	  header => 'dodgeburn.h',
	  symbols => [ qw(DODGE BURN) ],
	  mapping => { DODGE => '0',
		       BURN => '1' }
	},
    DodgeBurnMode =>
	{ contig => 1,
	  header => 'dodgeburn.h',
	  symbols => [ qw(DODGEBURN_HIGHLIGHTS DODGEBURN_MIDTONES
			  DODGEBURN_SHADOWS) ],
	  mapping => { DODGEBURN_HIGHLIGHTS => '0',
		       DODGEBURN_MIDTONES => '1',
		       DODGEBURN_SHADOWS => '2' }
	},
    OrientationType =>
	{ contig => 1,
	  header => 'gimpimage.h',
	  symbols => [ qw(HORIZONTAL VERTICAL UNKNOWN) ],
	  mapping => { HORIZONTAL => '0',
		       VERTICAL => '1',
		       UNKNOWN => '2' }
	},
    ChannelType =>
	{ contig => 1,
	  header => 'gimpimage.h',
	  symbols => [ qw(RED_CHANNEL GREEN_CHANNEL BLUE_CHANNEL
			  GRAY_CHANNEL INDEXED_CHANNEL AUXILLARY_CHANNEL) ],
	  mapping => { RED_CHANNEL => '0',
		       GREEN_CHANNEL => '1',
		       BLUE_CHANNEL => '2',
		       GRAY_CHANNEL => '3',
		       INDEXED_CHANNEL => '4',
		       AUXILLARY_CHANNEL => '5' }
	},
    MergeType =>
	{ contig => 1,
	  header => 'gimpimage.h',
	  symbols => [ qw(EXPAND_AS_NECESSARY CLIP_TO_IMAGE
			  CLIP_TO_BOTTOM_LAYER FLATTEN_IMAGE) ],
	  mapping => { EXPAND_AS_NECESSARY => '0',
		       CLIP_TO_IMAGE => '1',
		       CLIP_TO_BOTTOM_LAYER => '2',
		       FLATTEN_IMAGE => '3' }
	},
    HueRange =>
	{ contig => 1,
	  header => 'hue_saturation.h',
	  symbols => [ qw(ALL_HUES RED_HUES YELLOW_HUES GREEN_HUES CYAN_HUES
			  BLUE_HUES MAGENTA_HUES) ],
	  mapping => { ALL_HUES => '0',
		       RED_HUES => '1',
		       YELLOW_HUES => '2',
		       GREEN_HUES => '3',
		       CYAN_HUES => '4',
		       BLUE_HUES => '5',
		       MAGENTA_HUES => '6' }
	},
    ChannelLutType =>
	{ contig => 1,
	  header => 'lut_funcs.h',
	  symbols => [ qw(VALUE_LUT RED_LUT GREEN_LUT BLUE_LUT ALPHA_LUT) ],
	  mapping => { VALUE_LUT => '0',
		       RED_LUT => '1',
		       GREEN_LUT => '2',
		       BLUE_LUT => '3',
		       ALPHA_LUT => '4' }
	},
    RunModeType =>
	{ contig => 1,
	  header => 'plug_in.h',
	  symbols => [ qw(RUN_INTERACTIVE RUN_NONINTERACTIVE
			  RUN_WITH_LAST_VALS) ],
	  mapping => { RUN_INTERACTIVE => '0',
		       RUN_NONINTERACTIVE => '1',
		       RUN_WITH_LAST_VALS => '2' }
	},
    PDBArgType =>
	{ contig => 1,
	  header => 'procedural_db.h',
	  symbols => [ qw(PDB_INT32 PDB_INT16 PDB_INT8 PDB_FLOAT PDB_STRING
			  PDB_INT32ARRAY PDB_INT16ARRAY PDB_INT8ARRAY
			  PDB_FLOATARRAY PDB_STRINGARRAY PDB_COLOR
			  PDB_REGION PDB_DISPLAY PDB_IMAGE PDB_LAYER
			  PDB_CHANNEL PDB_DRAWABLE PDB_SELECTION
			  PDB_BOUNDARY PDB_PATH PDB_PARASITE PDB_STATUS
			  PDB_END) ],
	  mapping => { PDB_INT32 => '0',
		       PDB_INT16 => '1',
		       PDB_INT8 => '2',
		       PDB_FLOAT => '3',
		       PDB_STRING => '4',
		       PDB_INT32ARRAY => '5',
		       PDB_INT16ARRAY => '6',
		       PDB_INT8ARRAY => '7',
		       PDB_FLOATARRAY => '8',
		       PDB_STRINGARRAY => '9',
		       PDB_COLOR => '10',
		       PDB_REGION => '11',
		       PDB_DISPLAY => '12',
		       PDB_IMAGE => '13',
		       PDB_LAYER => '14',
		       PDB_CHANNEL => '15',
		       PDB_DRAWABLE => '16',
		       PDB_SELECTION => '17',
		       PDB_BOUNDARY => '18',
		       PDB_PATH => '19',
		       PDB_PARASITE => '20',
		       PDB_STATUS => '21',
		       PDB_END => '22' }
	},
    PDBStatusType =>
	{ contig => 1,
	  header => 'procedural_db.h',
	  symbols => [ qw(PDB_EXECUTION_ERROR PDB_CALLING_ERROR
			  PDB_PASS_THROUGH PDB_SUCCESS PDB_CANCEL) ],
	  mapping => { PDB_EXECUTION_ERROR => '0',
		       PDB_CALLING_ERROR => '1',
		       PDB_PASS_THROUGH => '2',
		       PDB_SUCCESS => '3',
		       PDB_CANCEL => '4' }
	},
    PDBProcType =>
	{ contig => 1,
	  header => 'procedural_db.h',
	  symbols => [ qw(PDB_INTERNAL PDB_PLUGIN PDB_EXTENSION
			  PDB_TEMPORARY) ],
	  mapping => { PDB_INTERNAL => '0',
		       PDB_PLUGIN => '1',
		       PDB_EXTENSION => '2',
		       PDB_TEMPORARY => '3' },
	  nicks   => { PDB_INTERNAL => 'INTERNAL',
		       PDB_PLUGIN => 'PLUGIN',
		       PDB_EXTENSION => 'EXTENSION',
		       PDB_TEMPORARY => 'TEMPORARY' }
	},
    SizeType =>
	{ contig => 1,
	  header => 'text_tool.h',
	  symbols => [ qw(PIXELS POINTS) ],
	  mapping => { PIXELS => '0',
		       POINTS => '1' }
	}
);

foreach $e (values %enums) {
    $e->{info} = "";
    foreach (@{$e->{symbols}}) {
	my $nick = exists $e->{nicks}->{$_} ? $e->{nicks}->{$_} : $_;
	$e->{info} .= "$nick ($e->{mapping}->{$_}), "
    }
    $e->{info} =~ s/, $//;
}

1;
