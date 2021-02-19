<script>
	import {
		onMount
	} from 'svelte';
	import Connect from './components/Connect.svelte';
	import SelectScan from './components/SelectScan.svelte';
	import Status from './components/Status.svelte';

	let data = {
		loading: true,
		connectStatus: {
			sent: false,
			success: true
		},
		selection: {
			direct_connect: false,
			selected: false,
			ssid: ''
		},
		access_points: []
	}

	function setConnectSuccess(){
		data.connectStatus.sent = true;
		data.connectStatus.success = true;
	}

	function setConnectError(){
		data.connectStatus.sent = true;
		data.connectStatus.success = false;
	}

	function clearSelection() {
		data.selection.selected = false;
		data.selection.direct_connect = false;
		data.selection.ssid = "";
	}

	function selectAccessPoint(event) {
		data.selection.ssid = event.detail.ssid
		if(event.detail.open){
			data.selection.direct_connect = true
		}
		data.selection.selected = true;
	}

	async function refresh (){ 
		data.loading = true
		await updateAccessPoints()
	}

	async function updateAccessPoints() {
		const res = await fetch(`/espconnect/scan`);
		if (res.status === 200) {
			data.access_points = await res.json();
			data.loading = false;
		}else if(res.status === 202) {
			setTimeout(updateAccessPoints, 2000);
		}
		return res;
	}

	onMount(async () => {
		try {
			await updateAccessPoints();
		} catch (err) {
			console.log(err);
		}
	});
</script>

<div class="container main-container">
	<div class="row">
		<div class="column text-center">
			<img
            src="data:image/png;base64,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"
            alt="ESP-Admin">
		</div>
	</div>
	<div class="row mb-2">
		<div class="column">
			<div class="card">
				{#if data.loading}
					<div class="container">
						<div class="row h-100">
							<div class="column text-center d-flex h-100">
								<div class="loader">
									<svg xmlns="http://www.w3.org/2000/svg" width="36" height="36" viewBox="0 0 24 24" style="fill: currentColor"><path d="M12,22c5.421,0,10-4.579,10-10h-2c0,4.337-3.663,8-8,8s-8-3.663-8-8c0-4.336,3.663-8,8-8V2C6.579,2,2,6.58,2,12 C2,17.421,6.579,22,12,22z"></path></svg>
								</div>
							</div>
						</div>
					</div>
				{:else}
					{#if !data.connectStatus.sent}
						{#if !data.selection.selected}
							<SelectScan access_points={data.access_points} on:refresh={refresh} on:select={selectAccessPoint} />
						{:else}
							<Connect ssid={data.selection.ssid} direct_connect={data.selection.direct_connect} on:back={clearSelection} on:success={setConnectSuccess} on:error={setConnectError} />
						{/if}
					{:else}
							<Status success={data.connectStatus.success} />
					{/if}
				{/if}
			</div>
		</div>
	</div>
</div>

<style type="text/scss" global>
	$color-primary: #353a41;
	$color-secondary: #202327;
	$color-muted: #626770;
	$color-quinary: #869ab8;
	
	$loader-color: #fff;
	$loader-size: 8px;
	$loader-height: 4px;
	$loader-border-size: 4px;
	$loader-gap: 6px;
	$loader-animation-duration: 1s;

	@import "../node_modules/milligram/src/milligram.sass";
	@import "../node_modules/spinthatshit/src/variables.scss";
	@import "../node_modules/spinthatshit/src/animations.scss";
	@import "../node_modules/spinthatshit/src/loaders/_loader10.scss";

	.text-muted{
		color: $color-muted !important;
	}

	.text-center{
		text-align: center;
	}

	.w-100{
		width: 100%;
	}

	.h-100{
		height: 100%;
	}

	.d-flex{
		display: flex !important;
	}

	.flex-columns{
		flex-direction: column;
	}

	.flex-rows{
		flex-direction: row;
	}

	.mb-2{
		margin-bottom: 2rem;
	}

	.pr-1{
		padding-right: 1rem;
	}

	.w-auto{
		width: auto !important;
	}

	.text-sm{
		font-size: 12px;
	}

	.clickable-row{
		padding: 1rem 0rem;
		border-bottom: 0.1rem solid #f4f5f6;
		transition: background-color .5s cubic-bezier(0.215, 0.610, 0.355, 1), box-shadow .5s cubic-bezier(0.215, 0.610, 0.355, 1);
		border-radius: .5rem;
		cursor: pointer;
		word-break: break-word;

		&:hover{
			box-shadow: rgba(99, 99, 99, 0.1) 0px 2px 8px 2px;
		}
	}

	input[type=text], input[type=password]{
		padding: 2.5rem 2rem !important;
		box-shadow: rgba(204, 219, 232, 0.2) 0px 3px 6px 1px inset, rgba(255, 255, 255, 0.4) 0px 0px 6px 6px inset;
		border: none;
		font-size: 16px !important;
	}

	input:disabled{
		background-color: rgba(47, 63, 82, 0.05);
		border: none;
	}

	.logo{
		margin: 5rem 1rem;
		fill: currentColor;
	}

	.main-container{
		max-width: 42rem !important;
		margin: 3rem auto;
	}

	.card{
		display: flex;
		position: relative;
		padding: 1rem;
		border-radius: 1rem;
		width: 100%;
		box-shadow: rgba(149, 157, 165, 0.15) 0px 8px 24px;
		min-height: 290px;

		.container{
			padding: 1rem 2rem;
		}
	}

	.button{
		border-radius: .5rem;
		transition: background-color .5s linear;
		box-shadow: rgba(149, 157, 165, 0.15) 0px 8px 24px !important;
		&[disabled]{
			opacity: 0.9;
		}
	}

	.btn-light{
		background-color:rgb(113, 121, 129) !important;
		border-color: rgb(113, 121, 129) !important;
	}

	.loader{
		margin: auto;
		svg {
			animation-name: spin;
			animation-duration: 1500ms;
			animation-iteration-count: infinite;
			animation-timing-function: linear; 
		}
	}

	@keyframes spin {
    from {
        transform:rotate(0deg);
    }
    to {
        transform:rotate(360deg);
    }
	}

	.btn-loader{
		margin: auto;
		@include loader10;
	}

</style>
