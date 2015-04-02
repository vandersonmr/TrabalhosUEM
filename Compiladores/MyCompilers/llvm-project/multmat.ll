; ModuleID = 'multmat.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %n = alloca i32, align 4
  %a = alloca i32*, align 8
  %b = alloca i32*, align 8
  %c = alloca i32*, align 8
  %i = alloca i32, align 4
  store i32 0, i32* %1
  store i32 750, i32* %n, align 4
  %2 = load i32* %n, align 4
  %3 = sext i32 %2 to i64
  %4 = mul i64 4, %3
  %5 = load i32* %n, align 4
  %6 = sext i32 %5 to i64
  %7 = mul i64 %4, %6
  %8 = call noalias i8* @malloc(i64 %7) #3
  %9 = bitcast i8* %8 to i32*
  store i32* %9, i32** %a, align 8
  %10 = load i32* %n, align 4
  %11 = sext i32 %10 to i64
  %12 = mul i64 4, %11
  %13 = load i32* %n, align 4
  %14 = sext i32 %13 to i64
  %15 = mul i64 %12, %14
  %16 = call noalias i8* @malloc(i64 %15) #3
  %17 = bitcast i8* %16 to i32*
  store i32* %17, i32** %b, align 8
  %18 = load i32* %n, align 4
  %19 = sext i32 %18 to i64
  %20 = mul i64 4, %19
  %21 = load i32* %n, align 4
  %22 = sext i32 %21 to i64
  %23 = mul i64 %20, %22
  %24 = call noalias i8* @malloc(i64 %23) #3
  %25 = bitcast i8* %24 to i32*
  store i32* %25, i32** %c, align 8
  store i32 0, i32* %i, align 4
  br label %26

; <label>:26                                      ; preds = %44, %0
  %27 = load i32* %i, align 4
  %28 = load i32* %n, align 4
  %29 = load i32* %n, align 4
  %30 = mul nsw i32 %28, %29
  %31 = icmp slt i32 %27, %30
  br i1 %31, label %32, label %47

; <label>:32                                      ; preds = %26
  %33 = load i32* %i, align 4
  %34 = load i32* %i, align 4
  %35 = sext i32 %34 to i64
  %36 = load i32** %a, align 8
  %37 = getelementptr inbounds i32* %36, i64 %35
  store i32 %33, i32* %37, align 4
  %38 = load i32* %i, align 4
  %39 = sdiv i32 %38, 2
  %40 = load i32* %i, align 4
  %41 = sext i32 %40 to i64
  %42 = load i32** %b, align 8
  %43 = getelementptr inbounds i32* %42, i64 %41
  store i32 %39, i32* %43, align 4
  br label %44

; <label>:44                                      ; preds = %32
  %45 = load i32* %i, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %i, align 4
  br label %26

; <label>:47                                      ; preds = %26
  %48 = load i32** %a, align 8
  %49 = load i32** %b, align 8
  %50 = load i32** %c, align 8
  %51 = load i32* %n, align 4
  call void @_Z8mult_matPiS_S_i(i32* %48, i32* %49, i32* %50, i32 %51)
  ret i32 0
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #1

; Function Attrs: nounwind uwtable
define void @_Z8mult_matPiS_S_i(i32* %a, i32* %b, i32* %c, i32 %n) #2 {
  %1 = alloca i32*, align 8
  %2 = alloca i32*, align 8
  %3 = alloca i32*, align 8
  %4 = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  store i32* %a, i32** %1, align 8
  store i32* %b, i32** %2, align 8
  store i32* %c, i32** %3, align 8
  store i32 %n, i32* %4, align 4
  store i32 0, i32* %i, align 4
  br label %5

; <label>:5                                       ; preds = %65, %0
  %6 = load i32* %i, align 4
  %7 = load i32* %4, align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %68

; <label>:9                                       ; preds = %5
  store i32 0, i32* %j, align 4
  br label %10

; <label>:10                                      ; preds = %61, %9
  %11 = load i32* %j, align 4
  %12 = load i32* %4, align 4
  %13 = icmp slt i32 %11, %12
  br i1 %13, label %14, label %64

; <label>:14                                      ; preds = %10
  %15 = load i32* %i, align 4
  %16 = load i32* %4, align 4
  %17 = load i32* %j, align 4
  %18 = mul nsw i32 %16, %17
  %19 = add nsw i32 %15, %18
  %20 = sext i32 %19 to i64
  %21 = load i32** %3, align 8
  %22 = getelementptr inbounds i32* %21, i64 %20
  store i32 0, i32* %22, align 4
  store i32 0, i32* %k, align 4
  br label %23

; <label>:23                                      ; preds = %57, %14
  %24 = load i32* %k, align 4
  %25 = load i32* %4, align 4
  %26 = icmp slt i32 %24, %25
  br i1 %26, label %27, label %60

; <label>:27                                      ; preds = %23
  %28 = load i32* %k, align 4
  %29 = load i32* %4, align 4
  %30 = load i32* %j, align 4
  %31 = mul nsw i32 %29, %30
  %32 = add nsw i32 %28, %31
  %33 = sext i32 %32 to i64
  %34 = load i32** %1, align 8
  %35 = getelementptr inbounds i32* %34, i64 %33
  %36 = load i32* %35, align 4
  %37 = load i32* %i, align 4
  %38 = load i32* %4, align 4
  %39 = load i32* %k, align 4
  %40 = mul nsw i32 %38, %39
  %41 = add nsw i32 %37, %40
  %42 = sext i32 %41 to i64
  %43 = load i32** %2, align 8
  %44 = getelementptr inbounds i32* %43, i64 %42
  %45 = load i32* %44, align 4
  %46 = mul nsw i32 %36, %45
  %47 = load i32* %i, align 4
  %48 = load i32* %4, align 4
  %49 = load i32* %j, align 4
  %50 = mul nsw i32 %48, %49
  %51 = add nsw i32 %47, %50
  %52 = sext i32 %51 to i64
  %53 = load i32** %3, align 8
  %54 = getelementptr inbounds i32* %53, i64 %52
  %55 = load i32* %54, align 4
  %56 = add nsw i32 %55, %46
  store i32 %56, i32* %54, align 4
  br label %57

; <label>:57                                      ; preds = %27
  %58 = load i32* %k, align 4
  %59 = add nsw i32 %58, 1
  store i32 %59, i32* %k, align 4
  br label %23

; <label>:60                                      ; preds = %23
  br label %61

; <label>:61                                      ; preds = %60
  %62 = load i32* %j, align 4
  %63 = add nsw i32 %62, 1
  store i32 %63, i32* %j, align 4
  br label %10

; <label>:64                                      ; preds = %10
  br label %65

; <label>:65                                      ; preds = %64
  %66 = load i32* %i, align 4
  %67 = add nsw i32 %66, 1
  store i32 %67, i32* %i, align 4
  br label %5

; <label>:68                                      ; preds = %5
  ret void
}

attributes #0 = { uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"}
