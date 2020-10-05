// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NonPlayerCharacter.h"
#include "CustomerData.h"
#include "AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Customer.generated.h"
/**
 * 
 */
class FCustomerDataRuntime;
class FCustomerGroup;
UCLASS()
class PROJECTINN_API ACustomer : public ANonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	/** Default UObject constructor. */
	ACustomer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintNativeEvent)
		void OnMouseLeftBtnClicked(AActor* focusedActor);
	    virtual void OnMouseLeftBtnClicked_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocused(AActor* focusedActor);
		virtual void OnMouseFocused_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocusLeft();
		void OnMouseFocusLeft_Implementation() override;

    UPROPERTY(EditAnywhere, Category = "Customer")
		FCustomerData CustomerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBlackboardData* InitBlackboardData;

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseLeftBtnClickedOnThis_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseFocusedOnThis_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseFocusLeft_BP();

	UFUNCTION(BlueprintCallable)
	UBlackboardComponent* GetBlackboardComponent() const;

	TWeakPtr<FCustomerGroup> GetBelongingGroup();

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Test_Move")
		void TestMove();

private:
	bool m_IsTicked = false;
	TSharedPtr<FCustomerDataRuntime> m_RuntimeData;
	UBlackboardComponent* m_CachedBlackboardComponent;
};
