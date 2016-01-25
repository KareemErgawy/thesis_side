; ModuleID = 'gaussian'
target datalayout = "e-p:64:64:64-S128-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f16:16:16-f32:32:32-f64:64:64-f128:128:128-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@0 = global [9 x i8] c"Timing: \00"
@1 = global [4 x i8] c" | \00"
@2 = global [4 x i8] c" | \00"
@3 = global [10 x i8] c" (median(\00"
@4 = global [27 x i8] c") | minimum | maximum) ms\0A\00"
@total_kernel_timing = global i64 0
@5 = global [32 x i8] c"Total timing for cpu / kernel: \00"
@total_cpu_timing = global i64 0
@6 = global [4 x i8] c" / \00"
@7 = global [5 x i8] c" ms\0A\00"
@8 = global [14 x i8] c"Test FAILED!\0A\00"
@9 = global [14 x i8] c"Test PASSED!\0A\00"
@10 = private unnamed_addr constant [19 x i8] c"lambda_crit_145894\00"
@11 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@12 = private unnamed_addr constant [19 x i8] c"lambda_crit_145239\00"
@13 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@14 = private unnamed_addr constant [19 x i8] c"lambda_crit_144476\00"
@15 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@16 = private unnamed_addr constant [19 x i8] c"lambda_crit_143862\00"
@17 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@18 = private unnamed_addr constant [19 x i8] c"lambda_crit_143381\00"
@19 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@20 = private unnamed_addr constant [19 x i8] c"lambda_crit_142769\00"
@21 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@22 = private unnamed_addr constant [19 x i8] c"lambda_crit_142005\00"
@23 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@24 = private unnamed_addr constant [19 x i8] c"lambda_crit_141351\00"
@25 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"
@26 = private unnamed_addr constant [19 x i8] c"lambda_crit_140589\00"
@27 = private unnamed_addr constant [12 x i8] c"gaussian.cl\00"

define i32 @main() {
alloc_cpu4:
  %0 = tail call i8* @thorin_alloc(i32 0, i64 67108864)
  %1 = tail call i8* @thorin_alloc(i32 0, i64 67108864)
  %2 = bitcast i8* %0 to [0 x float]*
  br label %if_then1166

if_else:                                          ; preds = %if_else1168
  %3 = bitcast i8* %1 to [0 x float]*
  br label %if_then1165

alloc17:                                          ; preds = %if_then1165
  %4 = tail call i8* @thorin_alloc(i32 18, i64 67108864)
  %5 = tail call i8* @thorin_alloc(i32 18, i64 67108864)
  tail call void @thorin_copy(i32 0, i8* %0, i64 0, i32 18, i8* %4, i64 0, i64 67108864)
  %6 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %7 = bitcast i8* %6 to [0 x i64]*
  br label %run_block1163

if_else20:                                        ; preds = %run_block1163
  %8 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 1
  %9 = load i64* %8
  %10 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 0
  %11 = load i64* %10
  %12 = icmp slt i64 %9, %11
  br i1 %12, label %next22, label %next_crit

next_crit:                                        ; preds = %if_else20
  store i64 %9, i64* %8
  br label %if_then

next22:                                           ; preds = %if_else20
  store i64 %11, i64* %8
  store i64 %9, i64* %10
  %.pre = load i64* %8
  br label %if_then

if_then:                                          ; preds = %next22, %next_crit
  %13 = phi i64 [ %.pre, %next22 ], [ %9, %next_crit ]
  %14 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 2
  %15 = load i64* %14
  %16 = icmp slt i64 %15, %13
  br i1 %16, label %and_extra29, label %next_crit24

next_crit24:                                      ; preds = %if_then
  store i64 %15, i64* %14
  br label %if_then32

and_extra29:                                      ; preds = %if_then
  store i64 %13, i64* %14
  %17 = load i64* %10
  %18 = icmp slt i64 %15, %17
  br i1 %18, label %while_body1157, label %next31

next31:                                           ; preds = %while_body1157, %and_extra29
  %.lcssa1332 = phi i64* [ %8, %and_extra29 ], [ %10, %while_body1157 ]
  store i64 %15, i64* %.lcssa1332
  %.pre1349 = load i64* %14
  br label %if_then32

if_then32:                                        ; preds = %next31, %next_crit24
  %19 = phi i64 [ %.pre1349, %next31 ], [ %15, %next_crit24 ]
  %20 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 3
  %21 = load i64* %20
  %22 = icmp slt i64 %21, %19
  br i1 %22, label %while_body36, label %next_crit35

next_crit35:                                      ; preds = %if_then32
  store i64 %21, i64* %20
  br label %if_then43

while_body36:                                     ; preds = %if_then32
  store i64 %19, i64* %20
  br label %and_extra40

and_extra40:                                      ; preds = %while_body36, %while_body1156
  %23 = phi i64* [ %14, %while_body36 ], [ %25, %while_body1156 ]
  %j381331 = phi i32 [ 2, %while_body36 ], [ %24, %while_body1156 ]
  %24 = add nsw i32 %j381331, -1
  %25 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 %24
  %26 = load i64* %25
  %27 = icmp slt i64 %21, %26
  br i1 %27, label %while_body1156, label %next42

next42:                                           ; preds = %and_extra40, %while_body1156
  %.lcssa1330 = phi i64* [ %23, %and_extra40 ], [ %25, %while_body1156 ]
  store i64 %21, i64* %.lcssa1330
  %.pre1350 = load i64* %20
  br label %if_then43

if_then43:                                        ; preds = %next42, %next_crit35
  %28 = phi i64 [ %.pre1350, %next42 ], [ %21, %next_crit35 ]
  %29 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 4
  %30 = load i64* %29
  %31 = icmp slt i64 %30, %28
  br i1 %31, label %while_body47, label %next_crit46

next_crit46:                                      ; preds = %if_then43
  store i64 %30, i64* %29
  br label %if_then54

while_body47:                                     ; preds = %if_then43
  store i64 %28, i64* %29
  br label %and_extra51

and_extra51:                                      ; preds = %while_body47, %while_body1155
  %32 = phi i64* [ %20, %while_body47 ], [ %34, %while_body1155 ]
  %j491329 = phi i32 [ 3, %while_body47 ], [ %33, %while_body1155 ]
  %33 = add nsw i32 %j491329, -1
  %34 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 %33
  %35 = load i64* %34
  %36 = icmp slt i64 %30, %35
  br i1 %36, label %while_body1155, label %next53

next53:                                           ; preds = %and_extra51, %while_body1155
  %.lcssa1328 = phi i64* [ %32, %and_extra51 ], [ %34, %while_body1155 ]
  store i64 %30, i64* %.lcssa1328
  %.pre1351 = load i64* %29
  br label %if_then54

if_then54:                                        ; preds = %next53, %next_crit46
  %37 = phi i64 [ %.pre1351, %next53 ], [ %30, %next_crit46 ]
  %38 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 5
  %39 = load i64* %38
  %40 = icmp slt i64 %39, %37
  br i1 %40, label %while_body58, label %next_crit57

next_crit57:                                      ; preds = %if_then54
  store i64 %39, i64* %38
  br label %if_then65

while_body58:                                     ; preds = %if_then54
  store i64 %37, i64* %38
  br label %and_extra62

and_extra62:                                      ; preds = %while_body58, %while_body1154
  %41 = phi i64* [ %29, %while_body58 ], [ %43, %while_body1154 ]
  %j601327 = phi i32 [ 4, %while_body58 ], [ %42, %while_body1154 ]
  %42 = add nsw i32 %j601327, -1
  %43 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 %42
  %44 = load i64* %43
  %45 = icmp slt i64 %39, %44
  br i1 %45, label %while_body1154, label %next64

next64:                                           ; preds = %and_extra62, %while_body1154
  %.lcssa1326 = phi i64* [ %41, %and_extra62 ], [ %43, %while_body1154 ]
  store i64 %39, i64* %.lcssa1326
  %.pre1352 = load i64* %38
  br label %if_then65

if_then65:                                        ; preds = %next64, %next_crit57
  %46 = phi i64 [ %.pre1352, %next64 ], [ %39, %next_crit57 ]
  %47 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 6
  %48 = load i64* %47
  %49 = icmp slt i64 %48, %46
  br i1 %49, label %while_body69, label %next_crit68

next_crit68:                                      ; preds = %if_then65
  store i64 %48, i64* %47
  br label %alloc86

while_body69:                                     ; preds = %if_then65
  store i64 %46, i64* %47
  br label %and_extra73

and_extra73:                                      ; preds = %while_body69, %while_body1153
  %50 = phi i64* [ %38, %while_body69 ], [ %52, %while_body1153 ]
  %j711325 = phi i32 [ 5, %while_body69 ], [ %51, %while_body1153 ]
  %51 = add nsw i32 %j711325, -1
  %52 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 %51
  %53 = load i64* %52
  %54 = icmp slt i64 %48, %53
  br i1 %54, label %while_body1153, label %next75

next75:                                           ; preds = %and_extra73, %while_body1153
  %.lcssa1324 = phi i64* [ %50, %and_extra73 ], [ %52, %while_body1153 ]
  store i64 %48, i64* %.lcssa1324
  br label %alloc86

alloc86:                                          ; preds = %next75, %next_crit68
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %55 = load i64* %20
  %56 = sitofp i64 %55 to double
  %57 = fdiv double %56, 1.000000e+03
  tail call void @thorin_print_double(double %57)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %58 = load i64* %10
  %59 = sitofp i64 %58 to double
  %60 = fdiv double %59, 1.000000e+03
  tail call void @thorin_print_double(double %60)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %61 = load i64* %47
  %62 = sitofp i64 %61 to double
  %63 = fdiv double %62, 1.000000e+03
  tail call void @thorin_print_double(double %63)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %64 = load i64* %20
  tail call void @thorin_release(i32 0, i8* %6)
  %65 = load i64* @total_kernel_timing
  %66 = add nsw i64 %65, %64
  store i64 %66, i64* @total_kernel_timing
  %67 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %68 = bitcast i8* %67 to [0 x i64]*
  br label %run_block1151

if_else89:                                        ; preds = %run_block1151
  %69 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 1
  %70 = load i64* %69
  %71 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 0
  %72 = load i64* %71
  %73 = icmp slt i64 %70, %72
  br i1 %73, label %next97, label %next_crit90

next_crit90:                                      ; preds = %if_else89
  store i64 %70, i64* %69
  br label %if_then98

next97:                                           ; preds = %if_else89
  store i64 %72, i64* %69
  store i64 %70, i64* %71
  %.pre1353 = load i64* %69
  br label %if_then98

if_then98:                                        ; preds = %next97, %next_crit90
  %74 = phi i64 [ %.pre1353, %next97 ], [ %70, %next_crit90 ]
  %75 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 2
  %76 = load i64* %75
  %77 = icmp slt i64 %76, %74
  br i1 %77, label %and_extra106, label %next_crit101

next_crit101:                                     ; preds = %if_then98
  store i64 %76, i64* %75
  br label %if_then109

and_extra106:                                     ; preds = %if_then98
  store i64 %74, i64* %75
  %78 = load i64* %71
  %79 = icmp slt i64 %76, %78
  br i1 %79, label %while_body1145, label %next108

next108:                                          ; preds = %while_body1145, %and_extra106
  %.lcssa1319 = phi i64* [ %69, %and_extra106 ], [ %71, %while_body1145 ]
  store i64 %76, i64* %.lcssa1319
  %.pre1354 = load i64* %75
  br label %if_then109

if_then109:                                       ; preds = %next108, %next_crit101
  %80 = phi i64 [ %.pre1354, %next108 ], [ %76, %next_crit101 ]
  %81 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 3
  %82 = load i64* %81
  %83 = icmp slt i64 %82, %80
  br i1 %83, label %while_body113, label %next_crit112

next_crit112:                                     ; preds = %if_then109
  store i64 %82, i64* %81
  br label %if_then120

while_body113:                                    ; preds = %if_then109
  store i64 %80, i64* %81
  br label %and_extra117

and_extra117:                                     ; preds = %while_body113, %while_body1144
  %84 = phi i64* [ %75, %while_body113 ], [ %86, %while_body1144 ]
  %j1151318 = phi i32 [ 2, %while_body113 ], [ %85, %while_body1144 ]
  %85 = add nsw i32 %j1151318, -1
  %86 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 %85
  %87 = load i64* %86
  %88 = icmp slt i64 %82, %87
  br i1 %88, label %while_body1144, label %next119

next119:                                          ; preds = %and_extra117, %while_body1144
  %.lcssa1317 = phi i64* [ %84, %and_extra117 ], [ %86, %while_body1144 ]
  store i64 %82, i64* %.lcssa1317
  %.pre1355 = load i64* %81
  br label %if_then120

if_then120:                                       ; preds = %next119, %next_crit112
  %89 = phi i64 [ %.pre1355, %next119 ], [ %82, %next_crit112 ]
  %90 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 4
  %91 = load i64* %90
  %92 = icmp slt i64 %91, %89
  br i1 %92, label %while_body124, label %next_crit123

next_crit123:                                     ; preds = %if_then120
  store i64 %91, i64* %90
  br label %if_then131

while_body124:                                    ; preds = %if_then120
  store i64 %89, i64* %90
  br label %and_extra128

and_extra128:                                     ; preds = %while_body124, %while_body1143
  %93 = phi i64* [ %81, %while_body124 ], [ %95, %while_body1143 ]
  %j1261316 = phi i32 [ 3, %while_body124 ], [ %94, %while_body1143 ]
  %94 = add nsw i32 %j1261316, -1
  %95 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 %94
  %96 = load i64* %95
  %97 = icmp slt i64 %91, %96
  br i1 %97, label %while_body1143, label %next130

next130:                                          ; preds = %and_extra128, %while_body1143
  %.lcssa1315 = phi i64* [ %93, %and_extra128 ], [ %95, %while_body1143 ]
  store i64 %91, i64* %.lcssa1315
  %.pre1356 = load i64* %90
  br label %if_then131

if_then131:                                       ; preds = %next130, %next_crit123
  %98 = phi i64 [ %.pre1356, %next130 ], [ %91, %next_crit123 ]
  %99 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 5
  %100 = load i64* %99
  %101 = icmp slt i64 %100, %98
  br i1 %101, label %while_body135, label %next_crit134

next_crit134:                                     ; preds = %if_then131
  store i64 %100, i64* %99
  br label %if_then142

while_body135:                                    ; preds = %if_then131
  store i64 %98, i64* %99
  br label %and_extra139

and_extra139:                                     ; preds = %while_body135, %while_body1142
  %102 = phi i64* [ %90, %while_body135 ], [ %104, %while_body1142 ]
  %j1371314 = phi i32 [ 4, %while_body135 ], [ %103, %while_body1142 ]
  %103 = add nsw i32 %j1371314, -1
  %104 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 %103
  %105 = load i64* %104
  %106 = icmp slt i64 %100, %105
  br i1 %106, label %while_body1142, label %next141

next141:                                          ; preds = %and_extra139, %while_body1142
  %.lcssa1313 = phi i64* [ %102, %and_extra139 ], [ %104, %while_body1142 ]
  store i64 %100, i64* %.lcssa1313
  %.pre1357 = load i64* %99
  br label %if_then142

if_then142:                                       ; preds = %next141, %next_crit134
  %107 = phi i64 [ %.pre1357, %next141 ], [ %100, %next_crit134 ]
  %108 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 6
  %109 = load i64* %108
  %110 = icmp slt i64 %109, %107
  br i1 %110, label %while_body146, label %next_crit145

next_crit145:                                     ; preds = %if_then142
  store i64 %109, i64* %108
  br label %alloc167

while_body146:                                    ; preds = %if_then142
  store i64 %107, i64* %108
  br label %and_extra150

and_extra150:                                     ; preds = %while_body146, %while_body1141
  %111 = phi i64* [ %99, %while_body146 ], [ %113, %while_body1141 ]
  %j1481312 = phi i32 [ 5, %while_body146 ], [ %112, %while_body1141 ]
  %112 = add nsw i32 %j1481312, -1
  %113 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 %112
  %114 = load i64* %113
  %115 = icmp slt i64 %109, %114
  br i1 %115, label %while_body1141, label %next152

next152:                                          ; preds = %and_extra150, %while_body1141
  %.lcssa1311 = phi i64* [ %111, %and_extra150 ], [ %113, %while_body1141 ]
  store i64 %109, i64* %.lcssa1311
  br label %alloc167

alloc167:                                         ; preds = %next152, %next_crit145
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %116 = load i64* %81
  %117 = sitofp i64 %116 to double
  %118 = fdiv double %117, 1.000000e+03
  tail call void @thorin_print_double(double %118)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %119 = load i64* %71
  %120 = sitofp i64 %119 to double
  %121 = fdiv double %120, 1.000000e+03
  tail call void @thorin_print_double(double %121)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %122 = load i64* %108
  %123 = sitofp i64 %122 to double
  %124 = fdiv double %123, 1.000000e+03
  tail call void @thorin_print_double(double %124)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %125 = load i64* %81
  tail call void @thorin_release(i32 0, i8* %67)
  %126 = load i64* @total_kernel_timing
  %127 = add nsw i64 %126, %125
  store i64 %127, i64* @total_kernel_timing
  %128 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %129 = bitcast i8* %128 to [0 x i64]*
  br label %run_block1139

if_else170:                                       ; preds = %run_block1139
  %130 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 1
  %131 = load i64* %130
  %132 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 0
  %133 = load i64* %132
  %134 = icmp slt i64 %131, %133
  br i1 %134, label %next178, label %next_crit171

next_crit171:                                     ; preds = %if_else170
  store i64 %131, i64* %130
  br label %if_then179

next178:                                          ; preds = %if_else170
  store i64 %133, i64* %130
  store i64 %131, i64* %132
  %.pre1358 = load i64* %130
  br label %if_then179

if_then179:                                       ; preds = %next178, %next_crit171
  %135 = phi i64 [ %.pre1358, %next178 ], [ %131, %next_crit171 ]
  %136 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 2
  %137 = load i64* %136
  %138 = icmp slt i64 %137, %135
  br i1 %138, label %and_extra187, label %next_crit182

next_crit182:                                     ; preds = %if_then179
  store i64 %137, i64* %136
  br label %if_then190

and_extra187:                                     ; preds = %if_then179
  store i64 %135, i64* %136
  %139 = load i64* %132
  %140 = icmp slt i64 %137, %139
  br i1 %140, label %while_body1133, label %next189

next189:                                          ; preds = %while_body1133, %and_extra187
  %.lcssa1306 = phi i64* [ %130, %and_extra187 ], [ %132, %while_body1133 ]
  store i64 %137, i64* %.lcssa1306
  %.pre1359 = load i64* %136
  br label %if_then190

if_then190:                                       ; preds = %next189, %next_crit182
  %141 = phi i64 [ %.pre1359, %next189 ], [ %137, %next_crit182 ]
  %142 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 3
  %143 = load i64* %142
  %144 = icmp slt i64 %143, %141
  br i1 %144, label %while_body194, label %next_crit193

next_crit193:                                     ; preds = %if_then190
  store i64 %143, i64* %142
  br label %if_then201

while_body194:                                    ; preds = %if_then190
  store i64 %141, i64* %142
  br label %and_extra198

and_extra198:                                     ; preds = %while_body194, %while_body1132
  %145 = phi i64* [ %136, %while_body194 ], [ %147, %while_body1132 ]
  %j1961305 = phi i32 [ 2, %while_body194 ], [ %146, %while_body1132 ]
  %146 = add nsw i32 %j1961305, -1
  %147 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 %146
  %148 = load i64* %147
  %149 = icmp slt i64 %143, %148
  br i1 %149, label %while_body1132, label %next200

next200:                                          ; preds = %and_extra198, %while_body1132
  %.lcssa1304 = phi i64* [ %145, %and_extra198 ], [ %147, %while_body1132 ]
  store i64 %143, i64* %.lcssa1304
  %.pre1360 = load i64* %142
  br label %if_then201

if_then201:                                       ; preds = %next200, %next_crit193
  %150 = phi i64 [ %.pre1360, %next200 ], [ %143, %next_crit193 ]
  %151 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 4
  %152 = load i64* %151
  %153 = icmp slt i64 %152, %150
  br i1 %153, label %while_body205, label %next_crit204

next_crit204:                                     ; preds = %if_then201
  store i64 %152, i64* %151
  br label %if_then212

while_body205:                                    ; preds = %if_then201
  store i64 %150, i64* %151
  br label %and_extra209

and_extra209:                                     ; preds = %while_body205, %while_body1131
  %154 = phi i64* [ %142, %while_body205 ], [ %156, %while_body1131 ]
  %j2071303 = phi i32 [ 3, %while_body205 ], [ %155, %while_body1131 ]
  %155 = add nsw i32 %j2071303, -1
  %156 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 %155
  %157 = load i64* %156
  %158 = icmp slt i64 %152, %157
  br i1 %158, label %while_body1131, label %next211

next211:                                          ; preds = %and_extra209, %while_body1131
  %.lcssa1302 = phi i64* [ %154, %and_extra209 ], [ %156, %while_body1131 ]
  store i64 %152, i64* %.lcssa1302
  %.pre1361 = load i64* %151
  br label %if_then212

if_then212:                                       ; preds = %next211, %next_crit204
  %159 = phi i64 [ %.pre1361, %next211 ], [ %152, %next_crit204 ]
  %160 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 5
  %161 = load i64* %160
  %162 = icmp slt i64 %161, %159
  br i1 %162, label %while_body216, label %next_crit215

next_crit215:                                     ; preds = %if_then212
  store i64 %161, i64* %160
  br label %if_then223

while_body216:                                    ; preds = %if_then212
  store i64 %159, i64* %160
  br label %and_extra220

and_extra220:                                     ; preds = %while_body216, %while_body1130
  %163 = phi i64* [ %151, %while_body216 ], [ %165, %while_body1130 ]
  %j2181301 = phi i32 [ 4, %while_body216 ], [ %164, %while_body1130 ]
  %164 = add nsw i32 %j2181301, -1
  %165 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 %164
  %166 = load i64* %165
  %167 = icmp slt i64 %161, %166
  br i1 %167, label %while_body1130, label %next222

next222:                                          ; preds = %and_extra220, %while_body1130
  %.lcssa1300 = phi i64* [ %163, %and_extra220 ], [ %165, %while_body1130 ]
  store i64 %161, i64* %.lcssa1300
  %.pre1362 = load i64* %160
  br label %if_then223

if_then223:                                       ; preds = %next222, %next_crit215
  %168 = phi i64 [ %.pre1362, %next222 ], [ %161, %next_crit215 ]
  %169 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 6
  %170 = load i64* %169
  %171 = icmp slt i64 %170, %168
  br i1 %171, label %while_body227, label %next_crit226

next_crit226:                                     ; preds = %if_then223
  store i64 %170, i64* %169
  br label %alloc248

while_body227:                                    ; preds = %if_then223
  store i64 %168, i64* %169
  br label %and_extra231

and_extra231:                                     ; preds = %while_body227, %while_body1129
  %172 = phi i64* [ %160, %while_body227 ], [ %174, %while_body1129 ]
  %j2291299 = phi i32 [ 5, %while_body227 ], [ %173, %while_body1129 ]
  %173 = add nsw i32 %j2291299, -1
  %174 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 %173
  %175 = load i64* %174
  %176 = icmp slt i64 %170, %175
  br i1 %176, label %while_body1129, label %next233

next233:                                          ; preds = %and_extra231, %while_body1129
  %.lcssa1298 = phi i64* [ %172, %and_extra231 ], [ %174, %while_body1129 ]
  store i64 %170, i64* %.lcssa1298
  br label %alloc248

alloc248:                                         ; preds = %next233, %next_crit226
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %177 = load i64* %142
  %178 = sitofp i64 %177 to double
  %179 = fdiv double %178, 1.000000e+03
  tail call void @thorin_print_double(double %179)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %180 = load i64* %132
  %181 = sitofp i64 %180 to double
  %182 = fdiv double %181, 1.000000e+03
  tail call void @thorin_print_double(double %182)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %183 = load i64* %169
  %184 = sitofp i64 %183 to double
  %185 = fdiv double %184, 1.000000e+03
  tail call void @thorin_print_double(double %185)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %186 = load i64* %142
  tail call void @thorin_release(i32 0, i8* %128)
  %187 = load i64* @total_kernel_timing
  %188 = add nsw i64 %187, %186
  store i64 %188, i64* @total_kernel_timing
  %189 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %190 = bitcast i8* %189 to [0 x i64]*
  br label %run_block1127

if_else251:                                       ; preds = %run_block1127
  %191 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 1
  %192 = load i64* %191
  %193 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 0
  %194 = load i64* %193
  %195 = icmp slt i64 %192, %194
  br i1 %195, label %next259, label %next_crit252

next_crit252:                                     ; preds = %if_else251
  store i64 %192, i64* %191
  br label %if_then260

next259:                                          ; preds = %if_else251
  store i64 %194, i64* %191
  store i64 %192, i64* %193
  %.pre1363 = load i64* %191
  br label %if_then260

if_then260:                                       ; preds = %next259, %next_crit252
  %196 = phi i64 [ %.pre1363, %next259 ], [ %192, %next_crit252 ]
  %197 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 2
  %198 = load i64* %197
  %199 = icmp slt i64 %198, %196
  br i1 %199, label %and_extra268, label %next_crit263

next_crit263:                                     ; preds = %if_then260
  store i64 %198, i64* %197
  br label %if_then271

and_extra268:                                     ; preds = %if_then260
  store i64 %196, i64* %197
  %200 = load i64* %193
  %201 = icmp slt i64 %198, %200
  br i1 %201, label %while_body1121, label %next270

next270:                                          ; preds = %while_body1121, %and_extra268
  %.lcssa1293 = phi i64* [ %191, %and_extra268 ], [ %193, %while_body1121 ]
  store i64 %198, i64* %.lcssa1293
  %.pre1364 = load i64* %197
  br label %if_then271

if_then271:                                       ; preds = %next270, %next_crit263
  %202 = phi i64 [ %.pre1364, %next270 ], [ %198, %next_crit263 ]
  %203 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 3
  %204 = load i64* %203
  %205 = icmp slt i64 %204, %202
  br i1 %205, label %while_body275, label %next_crit274

next_crit274:                                     ; preds = %if_then271
  store i64 %204, i64* %203
  br label %if_then282

while_body275:                                    ; preds = %if_then271
  store i64 %202, i64* %203
  br label %and_extra279

and_extra279:                                     ; preds = %while_body275, %while_body1120
  %206 = phi i64* [ %197, %while_body275 ], [ %208, %while_body1120 ]
  %j2771292 = phi i32 [ 2, %while_body275 ], [ %207, %while_body1120 ]
  %207 = add nsw i32 %j2771292, -1
  %208 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 %207
  %209 = load i64* %208
  %210 = icmp slt i64 %204, %209
  br i1 %210, label %while_body1120, label %next281

next281:                                          ; preds = %and_extra279, %while_body1120
  %.lcssa1291 = phi i64* [ %206, %and_extra279 ], [ %208, %while_body1120 ]
  store i64 %204, i64* %.lcssa1291
  %.pre1365 = load i64* %203
  br label %if_then282

if_then282:                                       ; preds = %next281, %next_crit274
  %211 = phi i64 [ %.pre1365, %next281 ], [ %204, %next_crit274 ]
  %212 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 4
  %213 = load i64* %212
  %214 = icmp slt i64 %213, %211
  br i1 %214, label %while_body286, label %next_crit285

next_crit285:                                     ; preds = %if_then282
  store i64 %213, i64* %212
  br label %if_then293

while_body286:                                    ; preds = %if_then282
  store i64 %211, i64* %212
  br label %and_extra290

and_extra290:                                     ; preds = %while_body286, %while_body1119
  %215 = phi i64* [ %203, %while_body286 ], [ %217, %while_body1119 ]
  %j2881290 = phi i32 [ 3, %while_body286 ], [ %216, %while_body1119 ]
  %216 = add nsw i32 %j2881290, -1
  %217 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 %216
  %218 = load i64* %217
  %219 = icmp slt i64 %213, %218
  br i1 %219, label %while_body1119, label %next292

next292:                                          ; preds = %and_extra290, %while_body1119
  %.lcssa1289 = phi i64* [ %215, %and_extra290 ], [ %217, %while_body1119 ]
  store i64 %213, i64* %.lcssa1289
  %.pre1366 = load i64* %212
  br label %if_then293

if_then293:                                       ; preds = %next292, %next_crit285
  %220 = phi i64 [ %.pre1366, %next292 ], [ %213, %next_crit285 ]
  %221 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 5
  %222 = load i64* %221
  %223 = icmp slt i64 %222, %220
  br i1 %223, label %while_body297, label %next_crit296

next_crit296:                                     ; preds = %if_then293
  store i64 %222, i64* %221
  br label %if_then304

while_body297:                                    ; preds = %if_then293
  store i64 %220, i64* %221
  br label %and_extra301

and_extra301:                                     ; preds = %while_body297, %while_body1118
  %224 = phi i64* [ %212, %while_body297 ], [ %226, %while_body1118 ]
  %j2991288 = phi i32 [ 4, %while_body297 ], [ %225, %while_body1118 ]
  %225 = add nsw i32 %j2991288, -1
  %226 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 %225
  %227 = load i64* %226
  %228 = icmp slt i64 %222, %227
  br i1 %228, label %while_body1118, label %next303

next303:                                          ; preds = %and_extra301, %while_body1118
  %.lcssa1287 = phi i64* [ %224, %and_extra301 ], [ %226, %while_body1118 ]
  store i64 %222, i64* %.lcssa1287
  %.pre1367 = load i64* %221
  br label %if_then304

if_then304:                                       ; preds = %next303, %next_crit296
  %229 = phi i64 [ %.pre1367, %next303 ], [ %222, %next_crit296 ]
  %230 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 6
  %231 = load i64* %230
  %232 = icmp slt i64 %231, %229
  br i1 %232, label %while_body308, label %next_crit307

next_crit307:                                     ; preds = %if_then304
  store i64 %231, i64* %230
  br label %alloc329

while_body308:                                    ; preds = %if_then304
  store i64 %229, i64* %230
  br label %and_extra312

and_extra312:                                     ; preds = %while_body308, %while_body1117
  %233 = phi i64* [ %221, %while_body308 ], [ %235, %while_body1117 ]
  %j3101286 = phi i32 [ 5, %while_body308 ], [ %234, %while_body1117 ]
  %234 = add nsw i32 %j3101286, -1
  %235 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 %234
  %236 = load i64* %235
  %237 = icmp slt i64 %231, %236
  br i1 %237, label %while_body1117, label %next314

next314:                                          ; preds = %and_extra312, %while_body1117
  %.lcssa1285 = phi i64* [ %233, %and_extra312 ], [ %235, %while_body1117 ]
  store i64 %231, i64* %.lcssa1285
  br label %alloc329

alloc329:                                         ; preds = %next314, %next_crit307
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %238 = load i64* %203
  %239 = sitofp i64 %238 to double
  %240 = fdiv double %239, 1.000000e+03
  tail call void @thorin_print_double(double %240)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %241 = load i64* %193
  %242 = sitofp i64 %241 to double
  %243 = fdiv double %242, 1.000000e+03
  tail call void @thorin_print_double(double %243)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %244 = load i64* %230
  %245 = sitofp i64 %244 to double
  %246 = fdiv double %245, 1.000000e+03
  tail call void @thorin_print_double(double %246)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %247 = load i64* %203
  tail call void @thorin_release(i32 0, i8* %189)
  %248 = load i64* @total_kernel_timing
  %249 = add nsw i64 %248, %247
  store i64 %249, i64* @total_kernel_timing
  %250 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %251 = bitcast i8* %250 to [0 x i64]*
  br label %run_block1115

if_else332:                                       ; preds = %run_block1115
  %252 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 1
  %253 = load i64* %252
  %254 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 0
  %255 = load i64* %254
  %256 = icmp slt i64 %253, %255
  br i1 %256, label %next340, label %next_crit333

next_crit333:                                     ; preds = %if_else332
  store i64 %253, i64* %252
  br label %if_then341

next340:                                          ; preds = %if_else332
  store i64 %255, i64* %252
  store i64 %253, i64* %254
  %.pre1368 = load i64* %252
  br label %if_then341

if_then341:                                       ; preds = %next340, %next_crit333
  %257 = phi i64 [ %.pre1368, %next340 ], [ %253, %next_crit333 ]
  %258 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 2
  %259 = load i64* %258
  %260 = icmp slt i64 %259, %257
  br i1 %260, label %and_extra349, label %next_crit344

next_crit344:                                     ; preds = %if_then341
  store i64 %259, i64* %258
  br label %if_then352

and_extra349:                                     ; preds = %if_then341
  store i64 %257, i64* %258
  %261 = load i64* %254
  %262 = icmp slt i64 %259, %261
  br i1 %262, label %while_body1109, label %next351

next351:                                          ; preds = %while_body1109, %and_extra349
  %.lcssa1280 = phi i64* [ %252, %and_extra349 ], [ %254, %while_body1109 ]
  store i64 %259, i64* %.lcssa1280
  %.pre1369 = load i64* %258
  br label %if_then352

if_then352:                                       ; preds = %next351, %next_crit344
  %263 = phi i64 [ %.pre1369, %next351 ], [ %259, %next_crit344 ]
  %264 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 3
  %265 = load i64* %264
  %266 = icmp slt i64 %265, %263
  br i1 %266, label %while_body356, label %next_crit355

next_crit355:                                     ; preds = %if_then352
  store i64 %265, i64* %264
  br label %if_then363

while_body356:                                    ; preds = %if_then352
  store i64 %263, i64* %264
  br label %and_extra360

and_extra360:                                     ; preds = %while_body356, %while_body1108
  %267 = phi i64* [ %258, %while_body356 ], [ %269, %while_body1108 ]
  %j3581279 = phi i32 [ 2, %while_body356 ], [ %268, %while_body1108 ]
  %268 = add nsw i32 %j3581279, -1
  %269 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 %268
  %270 = load i64* %269
  %271 = icmp slt i64 %265, %270
  br i1 %271, label %while_body1108, label %next362

next362:                                          ; preds = %and_extra360, %while_body1108
  %.lcssa1278 = phi i64* [ %267, %and_extra360 ], [ %269, %while_body1108 ]
  store i64 %265, i64* %.lcssa1278
  %.pre1370 = load i64* %264
  br label %if_then363

if_then363:                                       ; preds = %next362, %next_crit355
  %272 = phi i64 [ %.pre1370, %next362 ], [ %265, %next_crit355 ]
  %273 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 4
  %274 = load i64* %273
  %275 = icmp slt i64 %274, %272
  br i1 %275, label %while_body367, label %next_crit366

next_crit366:                                     ; preds = %if_then363
  store i64 %274, i64* %273
  br label %if_then374

while_body367:                                    ; preds = %if_then363
  store i64 %272, i64* %273
  br label %and_extra371

and_extra371:                                     ; preds = %while_body367, %while_body1107
  %276 = phi i64* [ %264, %while_body367 ], [ %278, %while_body1107 ]
  %j3691277 = phi i32 [ 3, %while_body367 ], [ %277, %while_body1107 ]
  %277 = add nsw i32 %j3691277, -1
  %278 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 %277
  %279 = load i64* %278
  %280 = icmp slt i64 %274, %279
  br i1 %280, label %while_body1107, label %next373

next373:                                          ; preds = %and_extra371, %while_body1107
  %.lcssa1276 = phi i64* [ %276, %and_extra371 ], [ %278, %while_body1107 ]
  store i64 %274, i64* %.lcssa1276
  %.pre1371 = load i64* %273
  br label %if_then374

if_then374:                                       ; preds = %next373, %next_crit366
  %281 = phi i64 [ %.pre1371, %next373 ], [ %274, %next_crit366 ]
  %282 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 5
  %283 = load i64* %282
  %284 = icmp slt i64 %283, %281
  br i1 %284, label %while_body378, label %next_crit377

next_crit377:                                     ; preds = %if_then374
  store i64 %283, i64* %282
  br label %if_then385

while_body378:                                    ; preds = %if_then374
  store i64 %281, i64* %282
  br label %and_extra382

and_extra382:                                     ; preds = %while_body378, %while_body1106
  %285 = phi i64* [ %273, %while_body378 ], [ %287, %while_body1106 ]
  %j3801275 = phi i32 [ 4, %while_body378 ], [ %286, %while_body1106 ]
  %286 = add nsw i32 %j3801275, -1
  %287 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 %286
  %288 = load i64* %287
  %289 = icmp slt i64 %283, %288
  br i1 %289, label %while_body1106, label %next384

next384:                                          ; preds = %and_extra382, %while_body1106
  %.lcssa1274 = phi i64* [ %285, %and_extra382 ], [ %287, %while_body1106 ]
  store i64 %283, i64* %.lcssa1274
  %.pre1372 = load i64* %282
  br label %if_then385

if_then385:                                       ; preds = %next384, %next_crit377
  %290 = phi i64 [ %.pre1372, %next384 ], [ %283, %next_crit377 ]
  %291 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 6
  %292 = load i64* %291
  %293 = icmp slt i64 %292, %290
  br i1 %293, label %while_body389, label %next_crit388

next_crit388:                                     ; preds = %if_then385
  store i64 %292, i64* %291
  br label %alloc410

while_body389:                                    ; preds = %if_then385
  store i64 %290, i64* %291
  br label %and_extra393

and_extra393:                                     ; preds = %while_body389, %while_body1105
  %294 = phi i64* [ %282, %while_body389 ], [ %296, %while_body1105 ]
  %j3911273 = phi i32 [ 5, %while_body389 ], [ %295, %while_body1105 ]
  %295 = add nsw i32 %j3911273, -1
  %296 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 %295
  %297 = load i64* %296
  %298 = icmp slt i64 %292, %297
  br i1 %298, label %while_body1105, label %next395

next395:                                          ; preds = %and_extra393, %while_body1105
  %.lcssa1272 = phi i64* [ %294, %and_extra393 ], [ %296, %while_body1105 ]
  store i64 %292, i64* %.lcssa1272
  br label %alloc410

alloc410:                                         ; preds = %next395, %next_crit388
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %299 = load i64* %264
  %300 = sitofp i64 %299 to double
  %301 = fdiv double %300, 1.000000e+03
  tail call void @thorin_print_double(double %301)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %302 = load i64* %254
  %303 = sitofp i64 %302 to double
  %304 = fdiv double %303, 1.000000e+03
  tail call void @thorin_print_double(double %304)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %305 = load i64* %291
  %306 = sitofp i64 %305 to double
  %307 = fdiv double %306, 1.000000e+03
  tail call void @thorin_print_double(double %307)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %308 = load i64* %264
  tail call void @thorin_release(i32 0, i8* %250)
  %309 = load i64* @total_kernel_timing
  %310 = add nsw i64 %309, %308
  store i64 %310, i64* @total_kernel_timing
  %311 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %312 = bitcast i8* %311 to [0 x i64]*
  br label %run_block1103

if_else413:                                       ; preds = %run_block1103
  %313 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 1
  %314 = load i64* %313
  %315 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 0
  %316 = load i64* %315
  %317 = icmp slt i64 %314, %316
  br i1 %317, label %next421, label %next_crit414

next_crit414:                                     ; preds = %if_else413
  store i64 %314, i64* %313
  br label %if_then422

next421:                                          ; preds = %if_else413
  store i64 %316, i64* %313
  store i64 %314, i64* %315
  %.pre1373 = load i64* %313
  br label %if_then422

if_then422:                                       ; preds = %next421, %next_crit414
  %318 = phi i64 [ %.pre1373, %next421 ], [ %314, %next_crit414 ]
  %319 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 2
  %320 = load i64* %319
  %321 = icmp slt i64 %320, %318
  br i1 %321, label %and_extra430, label %next_crit425

next_crit425:                                     ; preds = %if_then422
  store i64 %320, i64* %319
  br label %if_then433

and_extra430:                                     ; preds = %if_then422
  store i64 %318, i64* %319
  %322 = load i64* %315
  %323 = icmp slt i64 %320, %322
  br i1 %323, label %while_body1097, label %next432

next432:                                          ; preds = %while_body1097, %and_extra430
  %.lcssa1267 = phi i64* [ %313, %and_extra430 ], [ %315, %while_body1097 ]
  store i64 %320, i64* %.lcssa1267
  %.pre1374 = load i64* %319
  br label %if_then433

if_then433:                                       ; preds = %next432, %next_crit425
  %324 = phi i64 [ %.pre1374, %next432 ], [ %320, %next_crit425 ]
  %325 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 3
  %326 = load i64* %325
  %327 = icmp slt i64 %326, %324
  br i1 %327, label %while_body437, label %next_crit436

next_crit436:                                     ; preds = %if_then433
  store i64 %326, i64* %325
  br label %if_then444

while_body437:                                    ; preds = %if_then433
  store i64 %324, i64* %325
  br label %and_extra441

and_extra441:                                     ; preds = %while_body437, %while_body1096
  %328 = phi i64* [ %319, %while_body437 ], [ %330, %while_body1096 ]
  %j4391266 = phi i32 [ 2, %while_body437 ], [ %329, %while_body1096 ]
  %329 = add nsw i32 %j4391266, -1
  %330 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 %329
  %331 = load i64* %330
  %332 = icmp slt i64 %326, %331
  br i1 %332, label %while_body1096, label %next443

next443:                                          ; preds = %and_extra441, %while_body1096
  %.lcssa1265 = phi i64* [ %328, %and_extra441 ], [ %330, %while_body1096 ]
  store i64 %326, i64* %.lcssa1265
  %.pre1375 = load i64* %325
  br label %if_then444

if_then444:                                       ; preds = %next443, %next_crit436
  %333 = phi i64 [ %.pre1375, %next443 ], [ %326, %next_crit436 ]
  %334 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 4
  %335 = load i64* %334
  %336 = icmp slt i64 %335, %333
  br i1 %336, label %while_body448, label %next_crit447

next_crit447:                                     ; preds = %if_then444
  store i64 %335, i64* %334
  br label %if_then455

while_body448:                                    ; preds = %if_then444
  store i64 %333, i64* %334
  br label %and_extra452

and_extra452:                                     ; preds = %while_body448, %while_body1095
  %337 = phi i64* [ %325, %while_body448 ], [ %339, %while_body1095 ]
  %j4501264 = phi i32 [ 3, %while_body448 ], [ %338, %while_body1095 ]
  %338 = add nsw i32 %j4501264, -1
  %339 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 %338
  %340 = load i64* %339
  %341 = icmp slt i64 %335, %340
  br i1 %341, label %while_body1095, label %next454

next454:                                          ; preds = %and_extra452, %while_body1095
  %.lcssa1263 = phi i64* [ %337, %and_extra452 ], [ %339, %while_body1095 ]
  store i64 %335, i64* %.lcssa1263
  %.pre1376 = load i64* %334
  br label %if_then455

if_then455:                                       ; preds = %next454, %next_crit447
  %342 = phi i64 [ %.pre1376, %next454 ], [ %335, %next_crit447 ]
  %343 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 5
  %344 = load i64* %343
  %345 = icmp slt i64 %344, %342
  br i1 %345, label %while_body459, label %next_crit458

next_crit458:                                     ; preds = %if_then455
  store i64 %344, i64* %343
  br label %if_then466

while_body459:                                    ; preds = %if_then455
  store i64 %342, i64* %343
  br label %and_extra463

and_extra463:                                     ; preds = %while_body459, %while_body1094
  %346 = phi i64* [ %334, %while_body459 ], [ %348, %while_body1094 ]
  %j4611262 = phi i32 [ 4, %while_body459 ], [ %347, %while_body1094 ]
  %347 = add nsw i32 %j4611262, -1
  %348 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 %347
  %349 = load i64* %348
  %350 = icmp slt i64 %344, %349
  br i1 %350, label %while_body1094, label %next465

next465:                                          ; preds = %and_extra463, %while_body1094
  %.lcssa1261 = phi i64* [ %346, %and_extra463 ], [ %348, %while_body1094 ]
  store i64 %344, i64* %.lcssa1261
  %.pre1377 = load i64* %343
  br label %if_then466

if_then466:                                       ; preds = %next465, %next_crit458
  %351 = phi i64 [ %.pre1377, %next465 ], [ %344, %next_crit458 ]
  %352 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 6
  %353 = load i64* %352
  %354 = icmp slt i64 %353, %351
  br i1 %354, label %while_body470, label %next_crit469

next_crit469:                                     ; preds = %if_then466
  store i64 %353, i64* %352
  br label %alloc491

while_body470:                                    ; preds = %if_then466
  store i64 %351, i64* %352
  br label %and_extra474

and_extra474:                                     ; preds = %while_body470, %while_body1093
  %355 = phi i64* [ %343, %while_body470 ], [ %357, %while_body1093 ]
  %j4721260 = phi i32 [ 5, %while_body470 ], [ %356, %while_body1093 ]
  %356 = add nsw i32 %j4721260, -1
  %357 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 %356
  %358 = load i64* %357
  %359 = icmp slt i64 %353, %358
  br i1 %359, label %while_body1093, label %next476

next476:                                          ; preds = %and_extra474, %while_body1093
  %.lcssa1259 = phi i64* [ %355, %and_extra474 ], [ %357, %while_body1093 ]
  store i64 %353, i64* %.lcssa1259
  br label %alloc491

alloc491:                                         ; preds = %next476, %next_crit469
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %360 = load i64* %325
  %361 = sitofp i64 %360 to double
  %362 = fdiv double %361, 1.000000e+03
  tail call void @thorin_print_double(double %362)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %363 = load i64* %315
  %364 = sitofp i64 %363 to double
  %365 = fdiv double %364, 1.000000e+03
  tail call void @thorin_print_double(double %365)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %366 = load i64* %352
  %367 = sitofp i64 %366 to double
  %368 = fdiv double %367, 1.000000e+03
  tail call void @thorin_print_double(double %368)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %369 = load i64* %325
  tail call void @thorin_release(i32 0, i8* %311)
  %370 = load i64* @total_kernel_timing
  %371 = add nsw i64 %370, %369
  store i64 %371, i64* @total_kernel_timing
  %372 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %373 = bitcast i8* %372 to [0 x i64]*
  br label %run_block1091

if_else494:                                       ; preds = %run_block1091
  %374 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 1
  %375 = load i64* %374
  %376 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 0
  %377 = load i64* %376
  %378 = icmp slt i64 %375, %377
  br i1 %378, label %next502, label %next_crit495

next_crit495:                                     ; preds = %if_else494
  store i64 %375, i64* %374
  br label %if_then503

next502:                                          ; preds = %if_else494
  store i64 %377, i64* %374
  store i64 %375, i64* %376
  %.pre1378 = load i64* %374
  br label %if_then503

if_then503:                                       ; preds = %next502, %next_crit495
  %379 = phi i64 [ %.pre1378, %next502 ], [ %375, %next_crit495 ]
  %380 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 2
  %381 = load i64* %380
  %382 = icmp slt i64 %381, %379
  br i1 %382, label %and_extra511, label %next_crit506

next_crit506:                                     ; preds = %if_then503
  store i64 %381, i64* %380
  br label %if_then514

and_extra511:                                     ; preds = %if_then503
  store i64 %379, i64* %380
  %383 = load i64* %376
  %384 = icmp slt i64 %381, %383
  br i1 %384, label %while_body1085, label %next513

next513:                                          ; preds = %while_body1085, %and_extra511
  %.lcssa1254 = phi i64* [ %374, %and_extra511 ], [ %376, %while_body1085 ]
  store i64 %381, i64* %.lcssa1254
  %.pre1379 = load i64* %380
  br label %if_then514

if_then514:                                       ; preds = %next513, %next_crit506
  %385 = phi i64 [ %.pre1379, %next513 ], [ %381, %next_crit506 ]
  %386 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 3
  %387 = load i64* %386
  %388 = icmp slt i64 %387, %385
  br i1 %388, label %while_body518, label %next_crit517

next_crit517:                                     ; preds = %if_then514
  store i64 %387, i64* %386
  br label %if_then525

while_body518:                                    ; preds = %if_then514
  store i64 %385, i64* %386
  br label %and_extra522

and_extra522:                                     ; preds = %while_body518, %while_body1084
  %389 = phi i64* [ %380, %while_body518 ], [ %391, %while_body1084 ]
  %j5201253 = phi i32 [ 2, %while_body518 ], [ %390, %while_body1084 ]
  %390 = add nsw i32 %j5201253, -1
  %391 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 %390
  %392 = load i64* %391
  %393 = icmp slt i64 %387, %392
  br i1 %393, label %while_body1084, label %next524

next524:                                          ; preds = %and_extra522, %while_body1084
  %.lcssa1252 = phi i64* [ %389, %and_extra522 ], [ %391, %while_body1084 ]
  store i64 %387, i64* %.lcssa1252
  %.pre1380 = load i64* %386
  br label %if_then525

if_then525:                                       ; preds = %next524, %next_crit517
  %394 = phi i64 [ %.pre1380, %next524 ], [ %387, %next_crit517 ]
  %395 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 4
  %396 = load i64* %395
  %397 = icmp slt i64 %396, %394
  br i1 %397, label %while_body529, label %next_crit528

next_crit528:                                     ; preds = %if_then525
  store i64 %396, i64* %395
  br label %if_then536

while_body529:                                    ; preds = %if_then525
  store i64 %394, i64* %395
  br label %and_extra533

and_extra533:                                     ; preds = %while_body529, %while_body1083
  %398 = phi i64* [ %386, %while_body529 ], [ %400, %while_body1083 ]
  %j5311251 = phi i32 [ 3, %while_body529 ], [ %399, %while_body1083 ]
  %399 = add nsw i32 %j5311251, -1
  %400 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 %399
  %401 = load i64* %400
  %402 = icmp slt i64 %396, %401
  br i1 %402, label %while_body1083, label %next535

next535:                                          ; preds = %and_extra533, %while_body1083
  %.lcssa1250 = phi i64* [ %398, %and_extra533 ], [ %400, %while_body1083 ]
  store i64 %396, i64* %.lcssa1250
  %.pre1381 = load i64* %395
  br label %if_then536

if_then536:                                       ; preds = %next535, %next_crit528
  %403 = phi i64 [ %.pre1381, %next535 ], [ %396, %next_crit528 ]
  %404 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 5
  %405 = load i64* %404
  %406 = icmp slt i64 %405, %403
  br i1 %406, label %while_body540, label %next_crit539

next_crit539:                                     ; preds = %if_then536
  store i64 %405, i64* %404
  br label %if_then547

while_body540:                                    ; preds = %if_then536
  store i64 %403, i64* %404
  br label %and_extra544

and_extra544:                                     ; preds = %while_body540, %while_body1082
  %407 = phi i64* [ %395, %while_body540 ], [ %409, %while_body1082 ]
  %j5421249 = phi i32 [ 4, %while_body540 ], [ %408, %while_body1082 ]
  %408 = add nsw i32 %j5421249, -1
  %409 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 %408
  %410 = load i64* %409
  %411 = icmp slt i64 %405, %410
  br i1 %411, label %while_body1082, label %next546

next546:                                          ; preds = %and_extra544, %while_body1082
  %.lcssa1248 = phi i64* [ %407, %and_extra544 ], [ %409, %while_body1082 ]
  store i64 %405, i64* %.lcssa1248
  %.pre1382 = load i64* %404
  br label %if_then547

if_then547:                                       ; preds = %next546, %next_crit539
  %412 = phi i64 [ %.pre1382, %next546 ], [ %405, %next_crit539 ]
  %413 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 6
  %414 = load i64* %413
  %415 = icmp slt i64 %414, %412
  br i1 %415, label %while_body551, label %next_crit550

next_crit550:                                     ; preds = %if_then547
  store i64 %414, i64* %413
  br label %alloc572

while_body551:                                    ; preds = %if_then547
  store i64 %412, i64* %413
  br label %and_extra555

and_extra555:                                     ; preds = %while_body551, %while_body1081
  %416 = phi i64* [ %404, %while_body551 ], [ %418, %while_body1081 ]
  %j5531247 = phi i32 [ 5, %while_body551 ], [ %417, %while_body1081 ]
  %417 = add nsw i32 %j5531247, -1
  %418 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 %417
  %419 = load i64* %418
  %420 = icmp slt i64 %414, %419
  br i1 %420, label %while_body1081, label %next557

next557:                                          ; preds = %and_extra555, %while_body1081
  %.lcssa1246 = phi i64* [ %416, %and_extra555 ], [ %418, %while_body1081 ]
  store i64 %414, i64* %.lcssa1246
  br label %alloc572

alloc572:                                         ; preds = %next557, %next_crit550
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %421 = load i64* %386
  %422 = sitofp i64 %421 to double
  %423 = fdiv double %422, 1.000000e+03
  tail call void @thorin_print_double(double %423)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %424 = load i64* %376
  %425 = sitofp i64 %424 to double
  %426 = fdiv double %425, 1.000000e+03
  tail call void @thorin_print_double(double %426)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %427 = load i64* %413
  %428 = sitofp i64 %427 to double
  %429 = fdiv double %428, 1.000000e+03
  tail call void @thorin_print_double(double %429)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %430 = load i64* %386
  tail call void @thorin_release(i32 0, i8* %372)
  %431 = load i64* @total_kernel_timing
  %432 = add nsw i64 %431, %430
  store i64 %432, i64* @total_kernel_timing
  %433 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %434 = bitcast i8* %433 to [0 x i64]*
  br label %run_block1079

if_else575:                                       ; preds = %run_block1079
  %435 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 1
  %436 = load i64* %435
  %437 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 0
  %438 = load i64* %437
  %439 = icmp slt i64 %436, %438
  br i1 %439, label %next583, label %next_crit576

next_crit576:                                     ; preds = %if_else575
  store i64 %436, i64* %435
  br label %if_then584

next583:                                          ; preds = %if_else575
  store i64 %438, i64* %435
  store i64 %436, i64* %437
  %.pre1383 = load i64* %435
  br label %if_then584

if_then584:                                       ; preds = %next583, %next_crit576
  %440 = phi i64 [ %.pre1383, %next583 ], [ %436, %next_crit576 ]
  %441 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 2
  %442 = load i64* %441
  %443 = icmp slt i64 %442, %440
  br i1 %443, label %and_extra592, label %next_crit587

next_crit587:                                     ; preds = %if_then584
  store i64 %442, i64* %441
  br label %if_then595

and_extra592:                                     ; preds = %if_then584
  store i64 %440, i64* %441
  %444 = load i64* %437
  %445 = icmp slt i64 %442, %444
  br i1 %445, label %while_body1073, label %next594

next594:                                          ; preds = %while_body1073, %and_extra592
  %.lcssa1241 = phi i64* [ %435, %and_extra592 ], [ %437, %while_body1073 ]
  store i64 %442, i64* %.lcssa1241
  %.pre1384 = load i64* %441
  br label %if_then595

if_then595:                                       ; preds = %next594, %next_crit587
  %446 = phi i64 [ %.pre1384, %next594 ], [ %442, %next_crit587 ]
  %447 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 3
  %448 = load i64* %447
  %449 = icmp slt i64 %448, %446
  br i1 %449, label %while_body599, label %next_crit598

next_crit598:                                     ; preds = %if_then595
  store i64 %448, i64* %447
  br label %if_then606

while_body599:                                    ; preds = %if_then595
  store i64 %446, i64* %447
  br label %and_extra603

and_extra603:                                     ; preds = %while_body599, %while_body1072
  %450 = phi i64* [ %441, %while_body599 ], [ %452, %while_body1072 ]
  %j6011240 = phi i32 [ 2, %while_body599 ], [ %451, %while_body1072 ]
  %451 = add nsw i32 %j6011240, -1
  %452 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 %451
  %453 = load i64* %452
  %454 = icmp slt i64 %448, %453
  br i1 %454, label %while_body1072, label %next605

next605:                                          ; preds = %and_extra603, %while_body1072
  %.lcssa1239 = phi i64* [ %450, %and_extra603 ], [ %452, %while_body1072 ]
  store i64 %448, i64* %.lcssa1239
  %.pre1385 = load i64* %447
  br label %if_then606

if_then606:                                       ; preds = %next605, %next_crit598
  %455 = phi i64 [ %.pre1385, %next605 ], [ %448, %next_crit598 ]
  %456 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 4
  %457 = load i64* %456
  %458 = icmp slt i64 %457, %455
  br i1 %458, label %while_body610, label %next_crit609

next_crit609:                                     ; preds = %if_then606
  store i64 %457, i64* %456
  br label %if_then617

while_body610:                                    ; preds = %if_then606
  store i64 %455, i64* %456
  br label %and_extra614

and_extra614:                                     ; preds = %while_body610, %while_body1071
  %459 = phi i64* [ %447, %while_body610 ], [ %461, %while_body1071 ]
  %j6121238 = phi i32 [ 3, %while_body610 ], [ %460, %while_body1071 ]
  %460 = add nsw i32 %j6121238, -1
  %461 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 %460
  %462 = load i64* %461
  %463 = icmp slt i64 %457, %462
  br i1 %463, label %while_body1071, label %next616

next616:                                          ; preds = %and_extra614, %while_body1071
  %.lcssa1237 = phi i64* [ %459, %and_extra614 ], [ %461, %while_body1071 ]
  store i64 %457, i64* %.lcssa1237
  %.pre1386 = load i64* %456
  br label %if_then617

if_then617:                                       ; preds = %next616, %next_crit609
  %464 = phi i64 [ %.pre1386, %next616 ], [ %457, %next_crit609 ]
  %465 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 5
  %466 = load i64* %465
  %467 = icmp slt i64 %466, %464
  br i1 %467, label %while_body621, label %next_crit620

next_crit620:                                     ; preds = %if_then617
  store i64 %466, i64* %465
  br label %if_then628

while_body621:                                    ; preds = %if_then617
  store i64 %464, i64* %465
  br label %and_extra625

and_extra625:                                     ; preds = %while_body621, %while_body1070
  %468 = phi i64* [ %456, %while_body621 ], [ %470, %while_body1070 ]
  %j6231236 = phi i32 [ 4, %while_body621 ], [ %469, %while_body1070 ]
  %469 = add nsw i32 %j6231236, -1
  %470 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 %469
  %471 = load i64* %470
  %472 = icmp slt i64 %466, %471
  br i1 %472, label %while_body1070, label %next627

next627:                                          ; preds = %and_extra625, %while_body1070
  %.lcssa1235 = phi i64* [ %468, %and_extra625 ], [ %470, %while_body1070 ]
  store i64 %466, i64* %.lcssa1235
  %.pre1387 = load i64* %465
  br label %if_then628

if_then628:                                       ; preds = %next627, %next_crit620
  %473 = phi i64 [ %.pre1387, %next627 ], [ %466, %next_crit620 ]
  %474 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 6
  %475 = load i64* %474
  %476 = icmp slt i64 %475, %473
  br i1 %476, label %while_body632, label %next_crit631

next_crit631:                                     ; preds = %if_then628
  store i64 %475, i64* %474
  br label %alloc653

while_body632:                                    ; preds = %if_then628
  store i64 %473, i64* %474
  br label %and_extra636

and_extra636:                                     ; preds = %while_body632, %while_body1069
  %477 = phi i64* [ %465, %while_body632 ], [ %479, %while_body1069 ]
  %j6341234 = phi i32 [ 5, %while_body632 ], [ %478, %while_body1069 ]
  %478 = add nsw i32 %j6341234, -1
  %479 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 %478
  %480 = load i64* %479
  %481 = icmp slt i64 %475, %480
  br i1 %481, label %while_body1069, label %next638

next638:                                          ; preds = %and_extra636, %while_body1069
  %.lcssa1233 = phi i64* [ %477, %and_extra636 ], [ %479, %while_body1069 ]
  store i64 %475, i64* %.lcssa1233
  br label %alloc653

alloc653:                                         ; preds = %next638, %next_crit631
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %482 = load i64* %447
  %483 = sitofp i64 %482 to double
  %484 = fdiv double %483, 1.000000e+03
  tail call void @thorin_print_double(double %484)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %485 = load i64* %437
  %486 = sitofp i64 %485 to double
  %487 = fdiv double %486, 1.000000e+03
  tail call void @thorin_print_double(double %487)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %488 = load i64* %474
  %489 = sitofp i64 %488 to double
  %490 = fdiv double %489, 1.000000e+03
  tail call void @thorin_print_double(double %490)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %491 = load i64* %447
  tail call void @thorin_release(i32 0, i8* %433)
  %492 = load i64* @total_kernel_timing
  %493 = add nsw i64 %492, %491
  store i64 %493, i64* @total_kernel_timing
  %494 = tail call i8* @thorin_alloc(i32 0, i64 56)
  %495 = bitcast i8* %494 to [0 x i64]*
  br label %run_block1068

if_else656:                                       ; preds = %run_block1068
  %496 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 1
  %497 = load i64* %496
  %498 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 0
  %499 = load i64* %498
  %500 = icmp slt i64 %497, %499
  br i1 %500, label %next664, label %next_crit657

next_crit657:                                     ; preds = %if_else656
  store i64 %497, i64* %496
  br label %if_then665

next664:                                          ; preds = %if_else656
  store i64 %499, i64* %496
  store i64 %497, i64* %498
  %.pre1388 = load i64* %496
  br label %if_then665

if_then665:                                       ; preds = %next664, %next_crit657
  %501 = phi i64 [ %.pre1388, %next664 ], [ %497, %next_crit657 ]
  %502 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 2
  %503 = load i64* %502
  %504 = icmp slt i64 %503, %501
  br i1 %504, label %and_extra673, label %next_crit668

next_crit668:                                     ; preds = %if_then665
  store i64 %503, i64* %502
  br label %if_then676

and_extra673:                                     ; preds = %if_then665
  store i64 %501, i64* %502
  %505 = load i64* %498
  %506 = icmp slt i64 %503, %505
  br i1 %506, label %while_body1065, label %next675

next675:                                          ; preds = %while_body1065, %and_extra673
  %.lcssa1229 = phi i64* [ %496, %and_extra673 ], [ %498, %while_body1065 ]
  store i64 %503, i64* %.lcssa1229
  %.pre1389 = load i64* %502
  br label %if_then676

if_then676:                                       ; preds = %next675, %next_crit668
  %507 = phi i64 [ %.pre1389, %next675 ], [ %503, %next_crit668 ]
  %508 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 3
  %509 = load i64* %508
  %510 = icmp slt i64 %509, %507
  br i1 %510, label %while_body680, label %next_crit679

next_crit679:                                     ; preds = %if_then676
  store i64 %509, i64* %508
  br label %if_then687

while_body680:                                    ; preds = %if_then676
  store i64 %507, i64* %508
  br label %and_extra684

and_extra684:                                     ; preds = %while_body680, %while_body1064
  %511 = phi i64* [ %502, %while_body680 ], [ %513, %while_body1064 ]
  %j6821228 = phi i32 [ 2, %while_body680 ], [ %512, %while_body1064 ]
  %512 = add nsw i32 %j6821228, -1
  %513 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 %512
  %514 = load i64* %513
  %515 = icmp slt i64 %509, %514
  br i1 %515, label %while_body1064, label %next686

next686:                                          ; preds = %and_extra684, %while_body1064
  %.lcssa1227 = phi i64* [ %511, %and_extra684 ], [ %513, %while_body1064 ]
  store i64 %509, i64* %.lcssa1227
  %.pre1390 = load i64* %508
  br label %if_then687

if_then687:                                       ; preds = %next686, %next_crit679
  %516 = phi i64 [ %.pre1390, %next686 ], [ %509, %next_crit679 ]
  %517 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 4
  %518 = load i64* %517
  %519 = icmp slt i64 %518, %516
  br i1 %519, label %while_body691, label %next_crit690

next_crit690:                                     ; preds = %if_then687
  store i64 %518, i64* %517
  br label %if_then698

while_body691:                                    ; preds = %if_then687
  store i64 %516, i64* %517
  br label %and_extra695

and_extra695:                                     ; preds = %while_body691, %while_body1063
  %520 = phi i64* [ %508, %while_body691 ], [ %522, %while_body1063 ]
  %j6931226 = phi i32 [ 3, %while_body691 ], [ %521, %while_body1063 ]
  %521 = add nsw i32 %j6931226, -1
  %522 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 %521
  %523 = load i64* %522
  %524 = icmp slt i64 %518, %523
  br i1 %524, label %while_body1063, label %next697

next697:                                          ; preds = %and_extra695, %while_body1063
  %.lcssa1225 = phi i64* [ %520, %and_extra695 ], [ %522, %while_body1063 ]
  store i64 %518, i64* %.lcssa1225
  %.pre1391 = load i64* %517
  br label %if_then698

if_then698:                                       ; preds = %next697, %next_crit690
  %525 = phi i64 [ %.pre1391, %next697 ], [ %518, %next_crit690 ]
  %526 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 5
  %527 = load i64* %526
  %528 = icmp slt i64 %527, %525
  br i1 %528, label %while_body702, label %next_crit701

next_crit701:                                     ; preds = %if_then698
  store i64 %527, i64* %526
  br label %if_then709

while_body702:                                    ; preds = %if_then698
  store i64 %525, i64* %526
  br label %and_extra706

and_extra706:                                     ; preds = %while_body702, %while_body1062
  %529 = phi i64* [ %517, %while_body702 ], [ %531, %while_body1062 ]
  %j7041224 = phi i32 [ 4, %while_body702 ], [ %530, %while_body1062 ]
  %530 = add nsw i32 %j7041224, -1
  %531 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 %530
  %532 = load i64* %531
  %533 = icmp slt i64 %527, %532
  br i1 %533, label %while_body1062, label %next708

next708:                                          ; preds = %and_extra706, %while_body1062
  %.lcssa1223 = phi i64* [ %529, %and_extra706 ], [ %531, %while_body1062 ]
  store i64 %527, i64* %.lcssa1223
  %.pre1392 = load i64* %526
  br label %if_then709

if_then709:                                       ; preds = %next708, %next_crit701
  %534 = phi i64 [ %.pre1392, %next708 ], [ %527, %next_crit701 ]
  %535 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 6
  %536 = load i64* %535
  %537 = icmp slt i64 %536, %534
  br i1 %537, label %while_body713, label %next_crit712

next_crit712:                                     ; preds = %if_then709
  store i64 %536, i64* %535
  br label %print_total_timing739

while_body713:                                    ; preds = %if_then709
  store i64 %534, i64* %535
  br label %and_extra717

and_extra717:                                     ; preds = %while_body713, %while_body1061
  %538 = phi i64* [ %526, %while_body713 ], [ %540, %while_body1061 ]
  %j7151222 = phi i32 [ 5, %while_body713 ], [ %539, %while_body1061 ]
  %539 = add nsw i32 %j7151222, -1
  %540 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 %539
  %541 = load i64* %540
  %542 = icmp slt i64 %536, %541
  br i1 %542, label %while_body1061, label %next719

next719:                                          ; preds = %and_extra717, %while_body1061
  %.lcssa1221 = phi i64* [ %538, %and_extra717 ], [ %540, %while_body1061 ]
  store i64 %536, i64* %.lcssa1221
  br label %print_total_timing739

print_total_timing739:                            ; preds = %next_crit712, %next719
  tail call void @thorin_print_string([0 x i8]* bitcast ([9 x i8]* @0 to [0 x i8]*))
  %543 = load i64* %508
  %544 = sitofp i64 %543 to double
  %545 = fdiv double %544, 1.000000e+03
  tail call void @thorin_print_double(double %545)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @1 to [0 x i8]*))
  %546 = load i64* %498
  %547 = sitofp i64 %546 to double
  %548 = fdiv double %547, 1.000000e+03
  tail call void @thorin_print_double(double %548)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @2 to [0 x i8]*))
  %549 = load i64* %535
  %550 = sitofp i64 %549 to double
  %551 = fdiv double %550, 1.000000e+03
  tail call void @thorin_print_double(double %551)
  tail call void @thorin_print_string([0 x i8]* bitcast ([10 x i8]* @3 to [0 x i8]*))
  tail call void @thorin_print_int(i32 7)
  tail call void @thorin_print_string([0 x i8]* bitcast ([27 x i8]* @4 to [0 x i8]*))
  %552 = load i64* %508
  tail call void @thorin_release(i32 0, i8* %494)
  %553 = load i64* @total_kernel_timing
  %554 = add nsw i64 %553, %552
  store i64 %554, i64* @total_kernel_timing
  tail call void @thorin_copy(i32 18, i8* %5, i64 0, i32 0, i8* %1, i64 0, i64 67108864)
  tail call void @thorin_release(i32 18, i8* %4)
  tail call void @thorin_release(i32 18, i8* %5)
  tail call void @thorin_print_string([0 x i8]* bitcast ([32 x i8]* @5 to [0 x i8]*))
  %555 = load i64* @total_cpu_timing
  %556 = sitofp i64 %555 to double
  %557 = fdiv double %556, 1.000000e+03
  tail call void @thorin_print_double(double %557)
  tail call void @thorin_print_string([0 x i8]* bitcast ([4 x i8]* @6 to [0 x i8]*))
  %558 = load i64* @total_kernel_timing
  %559 = sitofp i64 %558 to double
  %560 = fdiv double %559, 1.000000e+03
  tail call void @thorin_print_double(double %560)
  tail call void @thorin_print_string([0 x i8]* bitcast ([5 x i8]* @7 to [0 x i8]*))
  %561 = addrspacecast i8* %0 to [0 x float] addrspace(1)*
  %562 = addrspacecast i8* %1 to [0 x float] addrspace(1)*
  br label %if_then749

range_step740.loopexit:                           ; preds = %range_step750
  %exitcond = icmp eq i32 %569, 4096
  br i1 %exitcond, label %if_else741, label %if_then749

if_else741:                                       ; preds = %range_step740.loopexit
  %563 = icmp eq i32 %passed751.ph, 0
  br i1 %563, label %if_then745, label %if_else743

if_else743:                                       ; preds = %if_else741
  tail call void @thorin_print_string([0 x i8]* bitcast ([14 x i8]* @8 to [0 x i8]*))
  br label %release748

if_then745:                                       ; preds = %if_else741
  tail call void @thorin_print_string([0 x i8]* bitcast ([14 x i8]* @9 to [0 x i8]*))
  br label %release748

release748:                                       ; preds = %if_then745, %if_else743
  tail call void @thorin_release(i32 0, i8* %0)
  tail call void @thorin_release(i32 0, i8* %1)
  ret i32 %passed751.ph

if_then749:                                       ; preds = %range_step740.loopexit, %print_total_timing739
  %passed1220 = phi i32 [ 0, %print_total_timing739 ], [ %passed751.ph, %range_step740.loopexit ]
  %564 = phi i32 [ 0, %print_total_timing739 ], [ %569, %range_step740.loopexit ]
  %565 = add nsw i32 %564, -2
  %566 = icmp slt i32 %565, 0
  %567 = add nsw i32 %564, -1
  %568 = icmp slt i32 %564, 1
  %569 = add nsw i32 %564, 1
  %570 = add nsw i32 %564, 2
  %571 = shl i32 %564, 12
  %.1171 = select i1 %566, i32 0, i32 %565
  %572 = icmp sgt i32 %.1171, 4095
  %.1181 = select i1 %568, i32 0, i32 %567
  %573 = icmp sgt i32 %.1181, 4095
  %574 = icmp sgt i32 %564, 4094
  %575 = icmp sgt i32 %570, 4095
  %.1171.op = shl i32 %.1171, 12
  %576 = select i1 %572, i32 16773120, i32 %.1171.op
  %.1181.op = shl i32 %.1181, 12
  %577 = select i1 %573, i32 16773120, i32 %.1181.op
  %.1201.op = shl i32 %569, 12
  %578 = select i1 %574, i32 16773120, i32 %.1201.op
  %.1211.op = shl i32 %570, 12
  %579 = select i1 %575, i32 16773120, i32 %.1211.op
  br label %range_step750.outer

range_step750.outer:                              ; preds = %next1056, %if_then749
  %.ph = phi i32 [ 0, %if_then749 ], [ %593, %next1056 ]
  %passed751.ph = phi i32 [ %passed1220, %if_then749 ], [ 42, %next1056 ]
  br label %range_step750

range_step750:                                    ; preds = %range_step750.outer, %next1056
  %580 = phi i32 [ %593, %next1056 ], [ %.ph, %range_step750.outer ]
  %581 = icmp slt i32 %580, 4096
  br i1 %581, label %if_then753, label %range_step740.loopexit

if_then753:                                       ; preds = %range_step750
  %582 = add nsw i32 %580, -2
  %583 = icmp slt i32 %582, 0
  %. = select i1 %583, i32 0, i32 %582
  %584 = icmp sgt i32 %., 4095
  %585 = select i1 %584, i32 4095, i32 %.
  %586 = add nsw i32 %580, -1
  %587 = icmp slt i32 %580, 1
  %.1172 = select i1 %587, i32 0, i32 %586
  %588 = icmp sgt i32 %.1172, 4095
  %589 = select i1 %588, i32 4095, i32 %.1172
  %590 = icmp slt i32 %580, 0
  %.1174 = select i1 %590, i32 0, i32 %580
  %591 = icmp sgt i32 %.1174, 4095
  %592 = select i1 %591, i32 4095, i32 %.1174
  %593 = add nsw i32 %580, 1
  %594 = icmp slt i32 %593, 0
  %.1176 = select i1 %594, i32 0, i32 %593
  %595 = icmp sgt i32 %.1176, 4095
  %596 = select i1 %595, i32 4095, i32 %.1176
  %597 = add nsw i32 %580, 2
  %598 = icmp slt i32 %597, 0
  %.1178 = select i1 %598, i32 0, i32 %597
  %599 = icmp sgt i32 %.1178, 4095
  %600 = select i1 %599, i32 4095, i32 %.1178
  %601 = add nsw i32 %585, %576
  %602 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %601
  %603 = add nsw i32 %589, %576
  %604 = load float addrspace(1)* %602
  %605 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %603
  %606 = add nsw i32 %592, %576
  %607 = load float addrspace(1)* %605
  %608 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %606
  %609 = add nsw i32 %596, %576
  %610 = load float addrspace(1)* %608
  %611 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %609
  %612 = add nsw i32 %600, %576
  %613 = load float addrspace(1)* %611
  %614 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %612
  %615 = add nsw i32 %585, %577
  %616 = load float addrspace(1)* %614
  %617 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %615
  %618 = add nsw i32 %589, %577
  %619 = load float addrspace(1)* %617
  %620 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %618
  %621 = add nsw i32 %592, %577
  %622 = load float addrspace(1)* %620
  %623 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %621
  %624 = add nsw i32 %596, %577
  %625 = load float addrspace(1)* %623
  %626 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %624
  %627 = add nsw i32 %600, %577
  %628 = load float addrspace(1)* %626
  %629 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %627
  %630 = add nsw i32 %585, %571
  %631 = load float addrspace(1)* %629
  %632 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %630
  %633 = add nsw i32 %589, %571
  %634 = load float addrspace(1)* %632
  %635 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %633
  %636 = add nsw i32 %592, %571
  %637 = load float addrspace(1)* %635
  %638 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %636
  %639 = add nsw i32 %596, %571
  %640 = load float addrspace(1)* %638
  %641 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %639
  %642 = add nsw i32 %600, %571
  %643 = load float addrspace(1)* %641
  %644 = fmul float %604, 0x3F748344C0000000
  %645 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %642
  %646 = fmul float %607, 0x3F91B71760000000
  %647 = fadd float %644, 0.000000e+00
  %648 = add nsw i32 %585, %578
  %649 = load float addrspace(1)* %645
  %650 = fmul float %610, 0x3F9AC753E0000000
  %651 = fadd float %647, %646
  %652 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %648
  %653 = fmul float %613, 0x3F91B71760000000
  %654 = fadd float %651, %650
  %655 = add nsw i32 %589, %578
  %656 = load float addrspace(1)* %652
  %657 = fmul float %616, 0x3F748344C0000000
  %658 = fadd float %654, %653
  %659 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %655
  %660 = fmul float %619, 0x3F91B71760000000
  %661 = fadd float %658, %657
  %662 = add nsw i32 %592, %578
  %663 = load float addrspace(1)* %659
  %664 = fmul float %622, 0x3FAE98FE60000000
  %665 = fadd float %661, %660
  %666 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %662
  %667 = fmul float %625, 0x3FB72074E0000000
  %668 = fadd float %665, %664
  %669 = add nsw i32 %596, %578
  %670 = load float addrspace(1)* %666
  %671 = fmul float %628, 0x3FAE98FE60000000
  %672 = fadd float %668, %667
  %673 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %669
  %674 = fmul float %631, 0x3F91B71760000000
  %675 = fadd float %672, %671
  %676 = add nsw i32 %600, %578
  %677 = load float addrspace(1)* %673
  %678 = fmul float %634, 0x3F9AC753E0000000
  %679 = fadd float %675, %674
  %680 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %676
  %681 = fmul float %637, 0x3FB72074E0000000
  %682 = fadd float %679, %678
  %683 = add nsw i32 %585, %579
  %684 = load float addrspace(1)* %680
  %685 = fmul float %640, 0x3FC17AF640000000
  %686 = fadd float %682, %681
  %687 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %683
  %688 = fmul float %643, 0x3FB72074E0000000
  %689 = fadd float %686, %685
  %690 = add nsw i32 %589, %579
  %691 = load float addrspace(1)* %687
  %692 = fmul float %649, 0x3F9AC753E0000000
  %693 = fadd float %689, %688
  %694 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %690
  %695 = fmul float %656, 0x3F91B71760000000
  %696 = fadd float %693, %692
  %697 = add nsw i32 %592, %579
  %698 = load float addrspace(1)* %694
  %699 = fmul float %663, 0x3FAE98FE60000000
  %700 = fadd float %696, %695
  %701 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %697
  %702 = fmul float %670, 0x3FB72074E0000000
  %703 = fadd float %700, %699
  %704 = add nsw i32 %596, %579
  %705 = load float addrspace(1)* %701
  %706 = fmul float %677, 0x3FAE98FE60000000
  %707 = fadd float %703, %702
  %708 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %704
  %709 = fmul float %684, 0x3F91B71760000000
  %710 = fadd float %707, %706
  %711 = add nsw i32 %600, %579
  %712 = load float addrspace(1)* %708
  %713 = fmul float %691, 0x3F748344C0000000
  %714 = fadd float %710, %709
  %715 = getelementptr inbounds [0 x float] addrspace(1)* %561, i64 0, i32 %711
  %716 = fmul float %698, 0x3F91B71760000000
  %717 = fadd float %714, %713
  %718 = add nsw i32 %580, %571
  %719 = load float addrspace(1)* %715
  %720 = fmul float %705, 0x3F9AC753E0000000
  %721 = fadd float %717, %716
  %722 = getelementptr inbounds [0 x float] addrspace(1)* %562, i64 0, i32 %718
  %723 = fmul float %712, 0x3F91B71760000000
  %724 = fadd float %721, %720
  %725 = load float addrspace(1)* %722
  %726 = fmul float %719, 0x3F748344C0000000
  %727 = fadd float %724, %723
  %728 = fadd float %727, %726
  %diff1170 = fsub float %728, %725
  %729 = fcmp olt float %diff1170, 0.000000e+00
  br i1 %729, label %if_then1055, label %next1056

if_then1055:                                      ; preds = %if_then753
  %730 = fsub float -0.000000e+00, %diff1170
  br label %next1056

next1056:                                         ; preds = %if_then753, %if_then1055
  %diff = phi float [ %730, %if_then1055 ], [ %diff1170, %if_then753 ]
  %731 = fcmp ogt float %diff, 0x3F847AE140000000
  br i1 %731, label %range_step750.outer, label %range_step750

while_body1061:                                   ; preds = %and_extra717
  store i64 %541, i64* %538
  %732 = icmp sgt i32 %539, 0
  br i1 %732, label %and_extra717, label %next719

while_body1062:                                   ; preds = %and_extra706
  store i64 %532, i64* %529
  %733 = icmp sgt i32 %530, 0
  br i1 %733, label %and_extra706, label %next708

while_body1063:                                   ; preds = %and_extra695
  store i64 %523, i64* %520
  %734 = icmp sgt i32 %521, 0
  br i1 %734, label %and_extra695, label %next697

while_body1064:                                   ; preds = %and_extra684
  store i64 %514, i64* %511
  %735 = icmp sgt i32 %512, 0
  br i1 %735, label %and_extra684, label %next686

while_body1065:                                   ; preds = %and_extra673
  store i64 %505, i64* %496
  br label %next675

run_block1068:                                    ; preds = %run_block1068, %alloc653
  %736 = phi i32 [ 0, %alloc653 ], [ %741, %run_block1068 ]
  %737 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @11, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @10, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %738 = tail call i64 @thorin_get_kernel_time()
  %739 = sub nsw i64 %738, %737
  %740 = getelementptr inbounds [0 x i64]* %495, i64 0, i32 %736
  %741 = add nsw i32 %736, 1
  store i64 %739, i64* %740
  %exitcond1337 = icmp eq i32 %741, 7
  br i1 %exitcond1337, label %if_else656, label %run_block1068

while_body1069:                                   ; preds = %and_extra636
  store i64 %480, i64* %477
  %742 = icmp sgt i32 %478, 0
  br i1 %742, label %and_extra636, label %next638

while_body1070:                                   ; preds = %and_extra625
  store i64 %471, i64* %468
  %743 = icmp sgt i32 %469, 0
  br i1 %743, label %and_extra625, label %next627

while_body1071:                                   ; preds = %and_extra614
  store i64 %462, i64* %459
  %744 = icmp sgt i32 %460, 0
  br i1 %744, label %and_extra614, label %next616

while_body1072:                                   ; preds = %and_extra603
  store i64 %453, i64* %450
  %745 = icmp sgt i32 %451, 0
  br i1 %745, label %and_extra603, label %next605

while_body1073:                                   ; preds = %and_extra592
  store i64 %444, i64* %435
  br label %next594

run_block1079:                                    ; preds = %run_block1079, %alloc572
  %746 = phi i32 [ 0, %alloc572 ], [ %751, %run_block1079 ]
  %747 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @13, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @12, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 4032, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %748 = tail call i64 @thorin_get_kernel_time()
  %749 = sub nsw i64 %748, %747
  %750 = getelementptr inbounds [0 x i64]* %434, i64 0, i32 %746
  %751 = add nsw i32 %746, 1
  store i64 %749, i64* %750
  %exitcond1338 = icmp eq i32 %751, 7
  br i1 %exitcond1338, label %if_else575, label %run_block1079

while_body1081:                                   ; preds = %and_extra555
  store i64 %419, i64* %416
  %752 = icmp sgt i32 %417, 0
  br i1 %752, label %and_extra555, label %next557

while_body1082:                                   ; preds = %and_extra544
  store i64 %410, i64* %407
  %753 = icmp sgt i32 %408, 0
  br i1 %753, label %and_extra544, label %next546

while_body1083:                                   ; preds = %and_extra533
  store i64 %401, i64* %398
  %754 = icmp sgt i32 %399, 0
  br i1 %754, label %and_extra533, label %next535

while_body1084:                                   ; preds = %and_extra522
  store i64 %392, i64* %389
  %755 = icmp sgt i32 %390, 0
  br i1 %755, label %and_extra522, label %next524

while_body1085:                                   ; preds = %and_extra511
  store i64 %383, i64* %374
  br label %next513

run_block1091:                                    ; preds = %run_block1091, %alloc491
  %756 = phi i32 [ 0, %alloc491 ], [ %761, %run_block1091 ]
  %757 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @15, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @14, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %758 = tail call i64 @thorin_get_kernel_time()
  %759 = sub nsw i64 %758, %757
  %760 = getelementptr inbounds [0 x i64]* %373, i64 0, i32 %756
  %761 = add nsw i32 %756, 1
  store i64 %759, i64* %760
  %exitcond1339 = icmp eq i32 %761, 7
  br i1 %exitcond1339, label %if_else494, label %run_block1091

while_body1093:                                   ; preds = %and_extra474
  store i64 %358, i64* %355
  %762 = icmp sgt i32 %356, 0
  br i1 %762, label %and_extra474, label %next476

while_body1094:                                   ; preds = %and_extra463
  store i64 %349, i64* %346
  %763 = icmp sgt i32 %347, 0
  br i1 %763, label %and_extra463, label %next465

while_body1095:                                   ; preds = %and_extra452
  store i64 %340, i64* %337
  %764 = icmp sgt i32 %338, 0
  br i1 %764, label %and_extra452, label %next454

while_body1096:                                   ; preds = %and_extra441
  store i64 %331, i64* %328
  %765 = icmp sgt i32 %329, 0
  br i1 %765, label %and_extra441, label %next443

while_body1097:                                   ; preds = %and_extra430
  store i64 %322, i64* %313
  br label %next432

run_block1103:                                    ; preds = %run_block1103, %alloc410
  %766 = phi i32 [ 0, %alloc410 ], [ %771, %run_block1103 ]
  %767 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @17, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @16, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4088, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %768 = tail call i64 @thorin_get_kernel_time()
  %769 = sub nsw i64 %768, %767
  %770 = getelementptr inbounds [0 x i64]* %312, i64 0, i32 %766
  %771 = add nsw i32 %766, 1
  store i64 %769, i64* %770
  %exitcond1340 = icmp eq i32 %771, 7
  br i1 %exitcond1340, label %if_else413, label %run_block1103

while_body1105:                                   ; preds = %and_extra393
  store i64 %297, i64* %294
  %772 = icmp sgt i32 %295, 0
  br i1 %772, label %and_extra393, label %next395

while_body1106:                                   ; preds = %and_extra382
  store i64 %288, i64* %285
  %773 = icmp sgt i32 %286, 0
  br i1 %773, label %and_extra382, label %next384

while_body1107:                                   ; preds = %and_extra371
  store i64 %279, i64* %276
  %774 = icmp sgt i32 %277, 0
  br i1 %774, label %and_extra371, label %next373

while_body1108:                                   ; preds = %and_extra360
  store i64 %270, i64* %267
  %775 = icmp sgt i32 %268, 0
  br i1 %775, label %and_extra360, label %next362

while_body1109:                                   ; preds = %and_extra349
  store i64 %261, i64* %252
  br label %next351

run_block1115:                                    ; preds = %run_block1115, %alloc329
  %776 = phi i32 [ 0, %alloc329 ], [ %781, %run_block1115 ]
  %777 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @19, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @18, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 4032, i32 4088, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %778 = tail call i64 @thorin_get_kernel_time()
  %779 = sub nsw i64 %778, %777
  %780 = getelementptr inbounds [0 x i64]* %251, i64 0, i32 %776
  %781 = add nsw i32 %776, 1
  store i64 %779, i64* %780
  %exitcond1341 = icmp eq i32 %781, 7
  br i1 %exitcond1341, label %if_else332, label %run_block1115

while_body1117:                                   ; preds = %and_extra312
  store i64 %236, i64* %233
  %782 = icmp sgt i32 %234, 0
  br i1 %782, label %and_extra312, label %next314

while_body1118:                                   ; preds = %and_extra301
  store i64 %227, i64* %224
  %783 = icmp sgt i32 %225, 0
  br i1 %783, label %and_extra301, label %next303

while_body1119:                                   ; preds = %and_extra290
  store i64 %218, i64* %215
  %784 = icmp sgt i32 %216, 0
  br i1 %784, label %and_extra290, label %next292

while_body1120:                                   ; preds = %and_extra279
  store i64 %209, i64* %206
  %785 = icmp sgt i32 %207, 0
  br i1 %785, label %and_extra279, label %next281

while_body1121:                                   ; preds = %and_extra268
  store i64 %200, i64* %191
  br label %next270

run_block1127:                                    ; preds = %run_block1127, %alloc248
  %786 = phi i32 [ 0, %alloc248 ], [ %791, %run_block1127 ]
  %787 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @21, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @20, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4088, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %788 = tail call i64 @thorin_get_kernel_time()
  %789 = sub nsw i64 %788, %787
  %790 = getelementptr inbounds [0 x i64]* %190, i64 0, i32 %786
  %791 = add nsw i32 %786, 1
  store i64 %789, i64* %790
  %exitcond1342 = icmp eq i32 %791, 7
  br i1 %exitcond1342, label %if_else251, label %run_block1127

while_body1129:                                   ; preds = %and_extra231
  store i64 %175, i64* %172
  %792 = icmp sgt i32 %173, 0
  br i1 %792, label %and_extra231, label %next233

while_body1130:                                   ; preds = %and_extra220
  store i64 %166, i64* %163
  %793 = icmp sgt i32 %164, 0
  br i1 %793, label %and_extra220, label %next222

while_body1131:                                   ; preds = %and_extra209
  store i64 %157, i64* %154
  %794 = icmp sgt i32 %155, 0
  br i1 %794, label %and_extra209, label %next211

while_body1132:                                   ; preds = %and_extra198
  store i64 %148, i64* %145
  %795 = icmp sgt i32 %146, 0
  br i1 %795, label %and_extra198, label %next200

while_body1133:                                   ; preds = %and_extra187
  store i64 %139, i64* %130
  br label %next189

run_block1139:                                    ; preds = %run_block1139, %alloc167
  %796 = phi i32 [ 0, %alloc167 ], [ %801, %run_block1139 ]
  %797 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @23, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @22, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %798 = tail call i64 @thorin_get_kernel_time()
  %799 = sub nsw i64 %798, %797
  %800 = getelementptr inbounds [0 x i64]* %129, i64 0, i32 %796
  %801 = add nsw i32 %796, 1
  store i64 %799, i64* %800
  %exitcond1343 = icmp eq i32 %801, 7
  br i1 %exitcond1343, label %if_else170, label %run_block1139

while_body1141:                                   ; preds = %and_extra150
  store i64 %114, i64* %111
  %802 = icmp sgt i32 %112, 0
  br i1 %802, label %and_extra150, label %next152

while_body1142:                                   ; preds = %and_extra139
  store i64 %105, i64* %102
  %803 = icmp sgt i32 %103, 0
  br i1 %803, label %and_extra139, label %next141

while_body1143:                                   ; preds = %and_extra128
  store i64 %96, i64* %93
  %804 = icmp sgt i32 %94, 0
  br i1 %804, label %and_extra128, label %next130

while_body1144:                                   ; preds = %and_extra117
  store i64 %87, i64* %84
  %805 = icmp sgt i32 %85, 0
  br i1 %805, label %and_extra117, label %next119

while_body1145:                                   ; preds = %and_extra106
  store i64 %78, i64* %69
  br label %next108

run_block1151:                                    ; preds = %run_block1151, %alloc86
  %806 = phi i32 [ 0, %alloc86 ], [ %811, %run_block1151 ]
  %807 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @25, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @24, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 4032, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %808 = tail call i64 @thorin_get_kernel_time()
  %809 = sub nsw i64 %808, %807
  %810 = getelementptr inbounds [0 x i64]* %68, i64 0, i32 %806
  %811 = add nsw i32 %806, 1
  store i64 %809, i64* %810
  %exitcond1344 = icmp eq i32 %811, 7
  br i1 %exitcond1344, label %if_else89, label %run_block1151

while_body1153:                                   ; preds = %and_extra73
  store i64 %53, i64* %50
  %812 = icmp sgt i32 %51, 0
  br i1 %812, label %and_extra73, label %next75

while_body1154:                                   ; preds = %and_extra62
  store i64 %44, i64* %41
  %813 = icmp sgt i32 %42, 0
  br i1 %813, label %and_extra62, label %next64

while_body1155:                                   ; preds = %and_extra51
  store i64 %35, i64* %32
  %814 = icmp sgt i32 %33, 0
  br i1 %814, label %and_extra51, label %next53

while_body1156:                                   ; preds = %and_extra40
  store i64 %26, i64* %23
  %815 = icmp sgt i32 %24, 0
  br i1 %815, label %and_extra40, label %next42

while_body1157:                                   ; preds = %and_extra29
  store i64 %17, i64* %8
  br label %next31

run_block1163:                                    ; preds = %run_block1163, %alloc17
  %816 = phi i32 [ 0, %alloc17 ], [ %821, %run_block1163 ]
  %817 = tail call i64 @thorin_get_kernel_time()
  tail call void @thorin_load_kernel(i32 18, i8* getelementptr inbounds ([12 x i8]* @27, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8]* @26, i32 0, i32 0))
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 0, i8* %5)
  tail call void @thorin_set_kernel_arg_ptr(i32 18, i32 1, i8* %4)
  tail call void @thorin_set_grid_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_set_block_size(i32 18, i32 32, i32 4, i32 1)
  tail call void @thorin_launch_kernel(i32 18)
  tail call void @thorin_synchronize(i32 18)
  %818 = tail call i64 @thorin_get_kernel_time()
  %819 = sub nsw i64 %818, %817
  %820 = getelementptr inbounds [0 x i64]* %7, i64 0, i32 %816
  %821 = add nsw i32 %816, 1
  store i64 %819, i64* %820
  %exitcond1345 = icmp eq i32 %821, 7
  br i1 %exitcond1345, label %if_else20, label %run_block1163

if_then1165:                                      ; preds = %if_then1165, %if_else
  %822 = phi i32 [ 0, %if_else ], [ %824, %if_then1165 ]
  %823 = getelementptr inbounds [0 x float]* %3, i64 0, i32 %822
  %824 = add nsw i32 %822, 1
  store float 0.000000e+00, float* %823
  %exitcond1346 = icmp eq i32 %824, 16777216
  br i1 %exitcond1346, label %alloc17, label %if_then1165

if_then1166:                                      ; preds = %if_else1168, %alloc_cpu4
  %825 = phi i32 [ 0, %alloc_cpu4 ], [ %827, %if_else1168 ]
  %826 = shl i32 %825, 12
  br label %lambda

if_else1168:                                      ; preds = %lambda
  %827 = add nsw i32 %825, 1
  %exitcond1348 = icmp eq i32 %827, 4096
  br i1 %exitcond1348, label %if_else, label %if_then1166

lambda:                                           ; preds = %lambda, %if_then1166
  %828 = phi i32 [ 0, %if_then1166 ], [ %833, %lambda ]
  %829 = tail call float @thorin_random_val()
  %830 = add nsw i32 %828, %826
  %831 = fmul float %829, 1.024000e+03
  %832 = getelementptr inbounds [0 x float]* %2, i64 0, i32 %830
  %833 = add nsw i32 %828, 1
  store float %831, float* %832
  %exitcond1347 = icmp eq i32 %833, 4096
  br i1 %exitcond1347, label %if_else1168, label %lambda
}

declare i8* @thorin_alloc(i32, i64)

declare void @thorin_copy(i32, i8*, i64, i32, i8*, i64, i64)

declare void @thorin_print_string([0 x i8]*)

declare void @thorin_print_double(double)

declare void @thorin_print_int(i32)

declare void @thorin_release(i32, i8*)

declare i64 @thorin_get_kernel_time()

declare void @thorin_load_kernel(i32, i8*, i8*)

declare void @thorin_set_kernel_arg_ptr(i32, i32, i8*)

declare void @thorin_set_grid_size(i32, i32, i32, i32)

declare void @thorin_set_block_size(i32, i32, i32, i32)

declare void @thorin_launch_kernel(i32)

declare void @thorin_synchronize(i32)

declare float @thorin_random_val()
